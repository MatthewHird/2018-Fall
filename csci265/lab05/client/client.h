#ifndef CLIENT_H
#define CLIENT_H


#include <cstdlib>
#include <cstring>
#include <string>
#include <netdb.h>
#include <iostream>
#include <unistd.h>
using namespace std;

// Maximum string lengths we'll process
const int MaxLength = 256;

// get the user to supply a hostname and port
void getHostInfo(char *hostname, char *port);

// get the necessary info and send a message
void sendMessage(char* hostname, char* port);

#endif

