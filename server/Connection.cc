#include "headers/Connection.h"

/*  Add exception throwing after cerrs  */
Connection::Connection(QObject *parent):
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

Connection::Connection(int PORT, QObject *parent) :
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

Connection::~Connection(){
    free(server);
}

int Connection::waitForRequest(string*){
    sock = server->nextPendingConnection();
    sock->write("SConnect");
    //sock->flush();
    /*  -1 make this block indefinitally. Change to timeout  */
    sock->waitForBytesWritten(-1);
    sock->waitForReadyRead(-1);
    qDebug()<<sock->readAll();
    return 0;
}

int Connection::sendResponse(string*){
  return 0;
}

