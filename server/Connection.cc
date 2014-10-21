#include "headers/Connection.h"

/*  Add exception throwing after cerrs  */
Connection::Connection(){
  port = 60001;
  olSock();

Connection::Connection(int PORT){
  port = PORT;
  olSock();
}

Connection::~Connection(){
  close(serverSock);
}

int Connection::waitForRequest(string*){
  return 0;
}

int Connection::sendResponse(string*){
  return 0;
}

int Connection::olSock(){
  if( (serverSock = socket(PF_INET, SOCK_STREAM, 0)) < 0 ){
    cerr<<"Could not open socket"<<endl;		
  } 
  bzero((char*) &serverAddr, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(port);

  if(bind(serverSock,(struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0){
    cerr<<"Could not bind to socket"<<endl;
  }

  if(listen(serverSock, 5) < 0){
    cerr<<"Could not listen"<<end;
  }
}
