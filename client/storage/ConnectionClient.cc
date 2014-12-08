#include "ConnectionClient.h"

ConnectionClient::ConnectionClient( QString *IPADDR, QObject *parent ): QObject(parent) {

    serverAddr = IPADDR;
    qDebug()<<*serverAddr;

    portno = 60001;
    sock = new QTcpSocket(this);

    connect(sock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayNetworkError(QAbstractSocket::SocketError)));

    sock->connectToHost(*serverAddr, portno);

}

ConnectionClient::ConnectionClient( QString *IPADDR, int PORT, QObject *parent ) : QObject(parent) {

    serverAddr = IPADDR;
    portno = PORT;
    sock = new QTcpSocket(this);

    connect(sock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayNetworkError(QAbstractSocket::SocketError)));

    sock->connectToHost(*serverAddr, portno);


}

ConnectionClient::~ConnectionClient() {

    sock->close();
    sock->disconnectFromHost();
    delete sock;

}

void ConnectionClient::request( QByteArray &inStr, QByteArray &outStr ) {


    // Test if still connected, if not try to connect again
    if (!sock->waitForConnected(100)) {
        sock->connectToHost(*serverAddr, portno);
        if (!sock->waitForConnected(100)) {
            emit ConnectionError("Could not connect to server");
            throw std::runtime_error("ERROR: ConnectionClient::request(), could not connect to server");
        }
    }

    if (sock->isValid() && sock->isWritable()) {
        if (sock->write(inStr) < 0)
            throw std::runtime_error("ERROR: ConnectionClient::request(), could not write request");
    }
    else {
        sock->abort();
        return;
    }

    /*  Recieve response from the server  */
    if (sock->isValid() && sock->isReadable()) {
        sock->waitForReadyRead(-1);
        QString inSize = sock->readLine();
        if (inSize.toInt() < 0)
            throw std::runtime_error("ERROR: ConnectionClient::request(), invalid message size");
        while (outStr.size() < inSize.toInt()) {
            outStr.append(sock->readLine());
        }
    }
    else {
        sock->abort();
        return;
    }


}

void ConnectionClient::displayNetworkError( QAbstractSocket::SocketError socketError ) {

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
