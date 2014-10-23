#include "headers/ConnectionClient.h"


ConnectionClient::ConnectionClient(string* IPADDR, QObject *parent):
    QObject(parent)
{

    serverAddr = new QString(IPADDR->c_str());
    portno = 60001;
    sock = new QTcpSocket(this);
}

ConnectionClient::ConnectionClient(string* IPADDR, int PORT, QObject *parent) :
    QObject(parent)
{
    serverAddr = new QString(IPADDR->c_str());
    portno = PORT;
    sock = new QTcpSocket(this);

}

int ConnectionClient::request(string * inStr, string *outStr){
    sock->connectToHost(*serverAddr, portno);
    sock->write(inStr->c_str());
    sock->waitForBytesWritten(-1);
    sock->waitForReadyRead(-1);
    char buf[256];
    sock->read(buf,255);
    outStr->append(buf);
    return 0;
}

