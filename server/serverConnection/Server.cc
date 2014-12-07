#include "Server.h"

Server::Server(DBController *cDb, QObject *parent) :
    QTcpServer(parent)
{
    db = cDb;
}


void Server::start(int port){
    portno = port;

    if (listen(QHostAddress::Any, portno))
        qDebug() << "Server is listening";
    else
       throw runtime_error("ERROR: ConnectionServer::ConnectionServer() Unable to start listening");
}

void Server::incomingConnection(qintptr sock)
{
    // At the incoming connection, make a client
    // and set the socket
    Connection *client = new Connection(db, this);
    client->setSocket(sock);
}
