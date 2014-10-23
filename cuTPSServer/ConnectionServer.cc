#include "headers/ConnectionServer.h"

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
    if(!server->hasPendingConnections())
        server->waitForNewConnection(-1);
    sock = server->nextPendingConnection();

    qDebug()<<"next connection found";
    sock->waitForBytesWritten(-1);
    sock->waitForReadyRead(-1);
    qDebug()<<"passed";
    char buf[256];
    sock->read(buf, 255);
    str->append(buf);
    return 0;
}

int ConnectionServer::sendResponse(string* str){
    sock->write(str->c_str());
    sock->disconnectFromHost();
  return 0;
}

