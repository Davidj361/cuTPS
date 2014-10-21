#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>       //bzero()
#include <unistd.h>
#include <sys/types.h>    //socket()
#include <sys/socket.h>   //socket()
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

class Connection{

  public:
    // default port is 60001
    Connection();

    /*  IN: int = port  */
    Connection(int);  

    /*  IN: str* = pointer to json object to be recieved or sent  */
    int waitForRequest(string*);
    int sendResponse(string*);

    ~Connection();

  private:
    int serverSock;
    int clientSock;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    unsigned short     port;

    /*  Open and listen on a socket  */
    int olSock();


};

#endif
