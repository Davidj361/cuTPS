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
    /*  Connect to the server and write the request  */
    sock->connectToHost(*serverAddr, portno);
    sock->write(inStr->c_str());
    sock->waitForBytesWritten(-1);

    /*  Recieve response from the server  */
    sock->waitForReadyRead(-1);
    char buf[256];
    int rv = sock->read(buf,255);
    buf[rv]='\0';
    outStr->append(buf);
    return 0;
}

