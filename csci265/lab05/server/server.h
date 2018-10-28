#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <fcntl.h>
#include "../key/keyPress.h"
using namespace std;

// default maximum string lengths
const int MaxLength = 256;

// time to wait between message checks
const int SleepTime = 5000000;

// get the appropriate sockaddr for the IP protocol,
//     IPv4 or IPv6
void *get_in_addr(struct sockaddr *sa);

// look up the host address information and attempt
//   to bind a socket for listening
// return the socket descriptor
int bindSocket(char *port);

// now let's just keep processing messages until the user
//     decides to quit
// the receives are blocking or not based on the blocking flag
void processMessages(int sockfd, bool blocking);

#endif

