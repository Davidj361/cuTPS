#include "Server.h"

Server::Server(DBController *cDb, QObject *parent) :
    QTcpServer(parent)
{

    db = cDb;

}


void Server::start(int port){

    portno = port;

    // start listening for connections
    if (listen(QHostAddress::Any, portno))
        qDebug() << "Server is listening";
    else
       throw std::runtime_error("Unable to start server. Port may already be in use by another program, or another instance of cuTPS server is already running.");
}

void Server::incomingConnection(qintptr sock) {

    // At the incoming connection, make a client
    // and set the socket
    Connection *client = new Connection(db, this);
    client->setSocket(sock);

}
