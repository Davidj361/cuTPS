#include "headers/ConnectionClient.h"

ConnectionClient::ConnectionClient(QString *IPADDR, QObject *parent): QObject(parent) {
  serverAddr = IPADDR;
  portno = 60001;
  sock = new QTcpSocket(this);
}

ConnectionClient::ConnectionClient(QString *IPADDR, int PORT, QObject *parent) : QObject(parent) {
  serverAddr = IPADDR;
  portno = PORT;
  sock = new QTcpSocket(this);
}

void ConnectionClient::request(QByteArray &inStr, QByteArray &outStr) {
  /*  Connect to the server and write the request  */
  //connect(sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(runTest3()));
  sock->connectToHost(*serverAddr, portno);
  sock->write(inStr);
  sock->waitForBytesWritten(-1);

  /*  Recieve response from the server  */
  sock->waitForReadyRead(-1);
  outStr = sock->readAll();
  sock->disconnectFromHost();
}

