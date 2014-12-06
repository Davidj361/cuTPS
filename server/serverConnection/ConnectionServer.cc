    #include "ConnectionServer.h"

ConnectionServer::ConnectionServer(QObject *parent): QObject(parent) {
    portno = 60001;
    server = new QTcpServer(this);

    if (!server->listen(QHostAddress::Any, portno))
        throw runtime_error("ERROR: ConnectionServer::ConnectionServer() Unable to start listening");
    else
        qDebug() << "Server is listening";
}

ConnectionServer::ConnectionServer(int PORT, QObject *parent) : QObject(parent) {
    portno = PORT;
    server = new QTcpServer(this);

    if (!server->listen(QHostAddress::Any, portno))
        throw runtime_error("ERROR: ConnectionServer::ConnectionServer() Unable to start listening");
    else
        qDebug() << "Server is listening";
}

ConnectionServer::~ConnectionServer() {
    delete server;
}

void ConnectionServer::newConnection(){

}

void ConnectionServer::WaitForRequest(QByteArray &str) {

    qDebug() << "Waiting for a connection";

    // Block until a connection is made by a client
    if (!server->hasPendingConnections())
        server->waitForNewConnection(-1);

    sock = server->nextPendingConnection();

    // Block until a message has been recieved
    qDebug() << "Found a connection";
    if (sock->waitForReadyRead(-1)) {
        str = sock->readAll();
    }
    else
        throw runtime_error("ERROR: ConnectionServer::WaitForRequest(), Error while waiting to read from socket");
}

void ConnectionServer::SendResponse(QByteArray &str) {
    // Turn size of message into QByteArray
    QString outSize = QString::number(str.size());
    QByteArray outSizearr;
    outSizearr.append(outSize);

    // Send size of message
    if (sock->write(outSizearr) < 0)
        throw runtime_error("ERROR: ConnectionServer::SendResponse(), Error while writing to socket");
    if (!sock->waitForBytesWritten(-1))
        throw runtime_error("ERROR: ConnectionServer::SendResponse(), Error while waiting for writing to socket to finish");

    sock->waitForReadyRead(-1);
    sock->readAll();

    // Send Message
    if (sock->write(str) < 0)
        throw runtime_error("ERROR: ConnectionServer::SendResponse(), Error while writing to socket");
    if (!sock->waitForBytesWritten(-1))
        throw runtime_error("ERROR: ConnectionServer::SendResponse(), Error while waiting for writing to socket to finish");

    qDebug() << "Disconnecting from client";
    sock->disconnectFromHost();
}

