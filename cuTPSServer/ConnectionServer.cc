#include "headers/ConnectionServer.h"
#include <unistd.h>

/*  Add exception throwing after cerrs  */
ConnectionServer::ConnectionServer(QObject *parent):
    QObject(parent)
{
    portno = 60001;
    server = new QTcpServer(this);
    if(!server->listen(QHostAddress::Any, portno)){
        qDebug() << "Server would not listen";
    }
    else{
        qDebug()<<"Server is listening";
    }
}

ConnectionServer::ConnectionServer(int PORT, QObject *parent) :
    QObject(parent)
{
    portno = PORT;
    server = new QTcpServer(this);
    if(!server->listen(QHostAddress::Any, portno)){
        qDebug() << "Server would not listen";
    }
    else{
        qDebug()<<"Server is listening";
    }
}

ConnectionServer::~ConnectionServer(){
    free(server);
}

int ConnectionServer::waitForRequest(string* str){
    /*  Block until a connection is made by a client  */
    qDebug()<<"Waiting for a connection";
    if(!server->hasPendingConnections())
        server->waitForNewConnection(-1);
    sock = server->nextPendingConnection();

    /*  Block until a message has been recieved  */
    qDebug()<<"Found a connection";
    int bytesread;
    if(sock->waitForReadyRead(-1)){
        char buf[256];
        if((bytesread = sock->read(buf, 255))<0){
            qDebug()<<"There was an error reading";
            return -1;
        }
        buf[bytesread] = '\0';
        str->append(buf);
        return 0;
    }
    else{
        qDebug()<<"There was an error waiting to read";
        return -1;
    }
}

int ConnectionServer::sendResponse(string* str){
    /*  Write message to client  */
    if(sock->write(str->c_str()) < 0){
        qDebug()<<"There was an error writing";
        return -1;
    }
    if(!sock->waitForBytesWritten(-1)){
        qDebug()<<"There was an error waiting for writing to finish";
        return -1;
    }
    qDebug()<<"Disconnecting from client";
    sock->disconnectFromHost();
  return 0;
}

