#include "headers/ConnectionClient.h"

ConnectionClient::ConnectionClient(QString* IPADDR, QObject *parent): QObject(parent) {
    serverAddr = IPADDR;
    portno = 60001;
    sock = new QTcpSocket(this);
}

ConnectionClient::ConnectionClient(QString* IPADDR, int PORT, QObject *parent) : QObject(parent) {
    serverAddr = IPADDR;
    portno = PORT;
    sock = new QTcpSocket(this);
}

int ConnectionClient::request(QByteArray * inStr, QByteArray *outStr) {
    /*  Connect to the server and write the request  */
    sock->connectToHost(*serverAddr, portno);
    sock->write(*inStr);
    sock->waitForBytesWritten(-1);

    /*  Recieve response from the server  */
    sock->waitForReadyRead(-1);
    char buf[256];
    int rv = sock->read(buf, 255);
    buf[rv]='\0';
    outStr->append(buf);
    return 0;
}

