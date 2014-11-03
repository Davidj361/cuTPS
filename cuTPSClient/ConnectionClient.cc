#include "headers/ConnectionClient.h"

ConnectionClient::ConnectionClient(QString *IPADDR, QObject *parent): QObject(parent) {
  serverAddr = IPADDR;
  portno = 60001;
  sock = new QTcpSocket(this);
  connect(sock, SIGNAL(error(QAbstractSocket::SocketError)),
          this, SLOT(displayNetworkError(QAbstractSocket::SocketError)));
}

ConnectionClient::ConnectionClient(QString *IPADDR, int PORT, QObject *parent) : QObject(parent) {
  serverAddr = IPADDR;
  portno = PORT;
  sock = new QTcpSocket(this);
  connect(sock, SIGNAL(error(QAbstractSocket::SocketError)),
          this, SLOT(displayNetworkError(QAbstractSocket::SocketError)));
}

void ConnectionClient::request(QByteArray &inStr, QByteArray &outStr) {
  /*  Connect to the server and write the request  */
  sock->connectToHost(*serverAddr, portno);
  // You have to make sure you're connected before you try to write anything. 
  // This was causing client spam because the program was doing write() and waitForBytesWritten() when it was still connecting.
  // TODO Add a #define that corresponds to non-functional requirement for maximum wait time of client
  if (sock->waitForConnected(1000))
          qDebug() << "************************* COULD NOT CONNECT TO SERVER! *************************";
  if (sock->isValid() && sock->isWritable()) {
    sock->write(inStr);
    sock->waitForBytesWritten(-1);
  }
  else {
      sock->abort();
      return;
  }

  /*  Recieve response from the server  */
  if (sock->isValid() && sock->isReadable()) {
      sock->waitForReadyRead(-1);
      outStr = sock->readAll();
  }
  else {
      sock->abort();
      return;
  }

  sock->close();
  sock->disconnectFromHost();
}

void ConnectionClient::displayNetworkError(QAbstractSocket::SocketError socketError)
{
    QString error = "";
    sock->abort();
    sock->close();

    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            return;
        case QAbstractSocket::HostNotFoundError:
            error = "The host was not found. Please check the host name and port settings.";
            break;
        case QAbstractSocket::ConnectionRefusedError:
            error = "The connection was refused by the peer. "
                                       "Make sure the server is running, "
                                       "and check that the host name and port "
                                       "settings are correct.";
            break;
        default:
            error = "The following error occurred: " + sock->errorString();
    }

    emit this->ConnectionError(error);
}
