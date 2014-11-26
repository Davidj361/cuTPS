#include "ConnectionClient.h"

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

ConnectionClient::~ConnectionClient() {
    delete sock;
}

void ConnectionClient::request(QByteArray &inStr, QByteArray &outStr) {

    /*  Connect to the server and write the request  */
    sock->connectToHost(*serverAddr, portno);

    if (!sock->waitForConnected(1000)) {
        emit ConnectionError("Could not connect to server");
        throw runtime_error("ERROR: ConnectionClient::request(), could not connect to server");
    }
    if (sock->isValid() && sock->isWritable()) {
        if (sock->write(inStr) < 0)
            throw runtime_error("ERROR: ConnectionClient::request(), could not write request");
    }
    else {
        sock->abort();
        return;
    }

    /*  Recieve response from the server  */
    if (sock->isValid() && sock->isReadable()) {
        sock->waitForReadyRead(-1);
        QByteArray inSize = sock->readAll();
        if (inSize.toInt() < 0)
            throw runtime_error("ERROR: ConnectionClient::request(), invalid message size");
        if (sock->write("ready") < 0)
            throw runtime_error("ERROR: ConnectionClient::request(), ready response was not sent");
        sock->waitForBytesWritten(-1);
        while (outStr.size() < inSize.toInt()) {
            sock->waitForReadyRead(-1);
            outStr.append(sock->readAll());
        }
    }
    else {
        sock->abort();
        return;
    }

    sock->close();
    sock->disconnectFromHost();
}

void ConnectionClient::displayNetworkError(QAbstractSocket::SocketError socketError) {

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
