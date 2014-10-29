#include "headers/ConnectionServer.h"

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
  free(server);
}


QByteArray *ConnectionServer::WaitForRequest() {

  QByteArray *str = new QByteArray();

  qDebug() << "Waiting for a connection";

  // Block until a connection is made by a client
  if (!server->hasPendingConnections())
    server->waitForNewConnection(-1);

  sock = server->nextPendingConnection();

  // Block until a message has been recieved
  qDebug() << "Found a connection";
  int bytesread;
  if (sock->waitForReadyRead(-1)) {
    char buf[256];

    if ((bytesread = sock->read(buf, 255)) < 0)
      throw runtime_error("ERROR: ConnectionServer::WaitForRequest(), Error while reading from socket");
    buf[bytesread] = '\0';
    str->append(buf);
  }
  else
    throw runtime_error("ERROR: ConnectionServer::WaitForRequest(), Error while waiting to read from socket");

  return str;
}

void ConnectionServer::SendResponse(QByteArray *str) {

  // Write message to client
  if (sock->write(*str) < 0)
    throw runtime_error("ERROR: ConnectionServer::SendResponse(), Error while writing to socket");

  if (!sock->waitForBytesWritten(-1))
    throw runtime_error("ERROR: ConnectionServer::SendResponse(), Error while waiting for writing to socket to finish");

  qDebug() << "Disconnecting from client";
  sock->disconnectFromHost();
}

