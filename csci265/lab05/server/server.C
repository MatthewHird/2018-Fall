// To listen for messages on port NNNN, run
//    server NNNN 
// To listen for messages on the default port, 4321, 
//    just run server with no command line arguments

#include "server.h"

// ===================================================================
//    MAIN ROUTINE
// ===================================================================

int main(int argc, char *argv[])
{
    // hostname of the current machine
    char hostname[MaxLength];
    gethostname(hostname, MaxLength-1);

    // port number to listen on, as text
    char port[MaxLength];

    // if a command line arg was supplied
    //    then use it as the port number,
    // otherwise use the default
    if (argc > 1) strncpy(port, argv[1], 5);
    else strncpy(port, "4321", 5);

    // display which host and port we're using
    cout << "\n*******************************" << endl << endl;
    cout << "Listening on host " << hostname << ", port " << port << "\n\n";
    float seconds = SleepTime/1000000.0;
    cout << "Checking for messages every " << seconds << " seconds\n\n";
    cout << "Enter Q when you are ready to quit\n\n";
    cout << "*******************************\n" << endl << endl;

    // initialize the socket descriptor for listening
    int sockfd = bindSocket(port);
    if (sockfd < 0) return -1;

    // now let's just keep processing messages until the user
    //     decides to quit
    // we'll specify non-blocking reads
    processMessages(sockfd, false);

    // close the socket and quit
    close(sockfd);
    return 0;
}

// ===================================================================
//    LISTENING ROUTINES
// ===================================================================

// get the appropriate sockaddr for the IP protocol,
//     IPv4 or IPv6
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
       // using IPv4
       return &(((struct sockaddr_in*)sa)->sin_addr);
    } else {
       // using IPv6
       return &(((struct sockaddr_in6*)sa)->sin6_addr);
    }
}

// look up the host address information and attempt
//   to bind a socket for listening
// return the socket descriptor
int bindSocket(char *port)
{
    // socket descriptor 
    int sockfd;

    // hints specifies the family/nature of valid address formats
    //   we want to search when prepping for socket binding
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);  // nullify initially
    hints.ai_family = AF_UNSPEC;      // accept IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM;   // UDP 
    hints.ai_flags = AI_PASSIVE;      // use my IP

    // find valid address info for the local host
    //    for the purpose of attempting socket binding,
    // storing the information in servinfo
    struct addrinfo *servinfo;
    int rv = getaddrinfo(NULL, port, &hints, &servinfo);
    if (rv != 0) {
        cerr << "***getaddrinfo: "  << gai_strerror(rv) << endl;
        return -1;
    }

    // loop through all the results and bind to the first we can
    struct addrinfo *p;
    for(p = servinfo; p != NULL; p = p->ai_next) {

        // try to bind with the given family, socket type, and protocol
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) {
            cerr << "***socket bind attempt failed\n";
        }

        // if that fails then try to bind by the address
        else if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            cerr << "***socket bind attempt failed\n";
        }

        // otherwise the bind succeeded, so escape the loop
        else break;
    }

    // if p is still null then everything we tried failed
    if (p == NULL) {
        cerr << "***all bind attempts failed\n";
        return -1;
    }

    // we no longer need the info on how to potentially set up
    //    a valid bind
    freeaddrinfo(servinfo);

    // return the socket descriptor
    return sockfd;
}

// now let's just keep processing messages until the user
//     decides to quit
// the receives are blocking or not based on the blocking flag
void processMessages(int sockfd, bool blocking)
{
    // set the socket to be blocking or not
    int flags = fcntl(sockfd, F_GETFL);
    if (!blocking) flags |= O_NONBLOCK;

    fcntl(sockfd, F_SETFL, flags);
    // now let's just keep processing messages until the user
    //     decides to quit
    bool quit = false;
    do {
       // storage buffer for incoming messages
       char msgBuf[MaxLength];

       cout << "checking for an incoming message...\n";

       // wait for a receive, and store who it came from
       struct sockaddr_storage their_addr;
       socklen_t addr_len = sizeof their_addr;
       int numbytes = recvfrom(sockfd, msgBuf, MaxLength-1 , 0, 
                           (struct sockaddr *)&their_addr, &addr_len);

       if (numbytes <= 0) {
           cout << "\n   No messages currently waiting\n";
       } else {
          // echo the received data and info after translating their
          //    address into a readable form (from binary)
          char readableAddr[INET6_ADDRSTRLEN]; 
          inet_ntop(their_addr.ss_family,
                    get_in_addr((struct sockaddr *)&their_addr),
                    readableAddr, sizeof readableAddr); 
          msgBuf[numbytes] = '\0';
          cout << "\n*************************" << endl;
          cout << "   received " << numbytes << " bytes from ";
          cout << readableAddr << endl;
          cout << "   contents \"" << msgBuf << "\"\n";
          cout << "*************************\n" << endl;
       }

       // see if the user wants to quit or wait for another message
       char cmd;
       if (keyQuick(cmd) && (cmd == 'q')) quit = true;
       else usleep(SleepTime);
    } while (!quit);
}

