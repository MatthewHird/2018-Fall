// Allows you to send one or more messages to a known host

#include "client.h"

int main(int argc, char *argv[])
{
   // set a default host and port
   char hostname[MaxLength], port[MaxLength];
   strcpy(hostname, "localhost");
   strcpy(port, "4321");

   // process user commands until they decide to quit
   bool quit;
   do {
      // give the user their command options and obtain their response
      cout << "Enter Q to quit," << endl;
      cout << "      H to set the host/port to send to\n";
      cout << "      M to send a message" << endl;
      cout << "   or D to display this menu" << endl;
      // read in the command
      string cmd; cin >> cmd; 
      // clear out the end of line character
      char newline; cin.get(newline);

      // handle whichever command they chose
      if ((cmd[0] == 'Q') || (cmd[0] == 'q')) 
         quit = true;
      else if ((cmd[0] == 'H') || (cmd[0] == 'h')) 
         getHostInfo(hostname, port);
      else if ((cmd[0] == 'M') || (cmd[0] == 'm')) 
         sendMessage(hostname, port);
      else
         cout << "Invalid command entered \"" << cmd << "\"\n";

      // keep processing commands until they decide to quit
   } while (!quit);
   return 0;
}

// get the user to supply a hostname and port
// (currently used in response to the H command)
void getHostInfo(char *hostname, char *port)
{
   cout << "Enter the hostname you want to talk to, e.g. pup1" << endl;
   cin.getline(hostname, MaxLength-1);
   do {
      cout << "Enter the port you want to connect to, e.g. 4321\n";
      cin.getline(port, MaxLength-1);
      // check that the port they specified is one we can actually use
   } while ((atoi(port) <= 2048) || (atoi(port) > 49152));
}

// given the current target host/port, get a message from
// the user and send it to the server at that location
// (currently used in response to the M command)
void sendMessage(char* hostname, char* port)
{
   // get the message the user wishes to send
   char message[MaxLength];
   cout << "Please enter the message you want to send (max ";
   cout << (MaxLength-1) << " characters)" << endl;
   cin.getline(message, MaxLength-1);

   // hints specifies the family/nature of valid address formats
   //   we want to search when prepping for socket binding
   // we're setting it up for a udp transmission
   struct addrinfo hints;
   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_DGRAM;

   // lookup valid address info for the host/port
   //    for the purpose of attempting socket binding,
   // storing the information in servinfo
   struct addrinfo *servinfo;
   int rv = getaddrinfo(hostname, port, &hints, &servinfo);
   if (rv != 0) {
      cerr << "***getaddrinfo: " << gai_strerror(rv) << endl;
   }

   // the servinfo struct has now been loaded with various possible
   //     descriptors for the server - we'll loop through these
   //     and bind our socket to the first one that succeeds
   int sockfd; // socket descriptor 
   struct addrinfo *p;
   for(p = servinfo; p != NULL; p = p->ai_next) {
      // try to bind with the given family, socket type, and protocol
      sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

      // if it fails print an error message and we'll
      //    move on to the next family/protocol (if any)
      if (sockfd == -1) {
         cerr << "***socket bind attempt failed\n";
      } 
  
      // otherwise it succeeded, escape the loop
      else break;
   }

   // if p is still null then everything we tried failed
   if (p == NULL) {
      cerr << "***all attempts failed to bind socket\n";
   }

   // we no longer need the info on how to potentially set up
   //    a valid bind
   freeaddrinfo(servinfo);

   // attempt to send the message
   int numbytes = sendto(sockfd, message, strlen(message), 0,
                                 p->ai_addr, p->ai_addrlen);

   // if it failed print an error message
   if (numbytes == -1) {
      cerr <<  "***sendto failed";
   }

   // otherwise summarize the results
   else {
      cout <<  "sent " << numbytes << " bytes to ";
      cout << hostname << endl;
   }

   // close the socket
   close(sockfd);
}

