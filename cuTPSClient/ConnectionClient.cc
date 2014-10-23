#include "headers/ConnectionClient.h"


ConnectionClient::ConnectionClient(char* IPADDR, QObject *parent):
    QObject(parent)
{
    serverAddr = new QString(IPADDR);
    portno = 60001;
    sock = new QTcpSocket(this);
}

ConnectionClient::ConnectionClient(string* IPADDR, int PORT, QObject *parent) :
    QObject(parent)
{
    *serverAddr = QString::fromStdString(*IPADDR);
    portno = PORT;
    sock = new QTcpSocket(this);
}


int ConnectionClient::sendRequest(string*){
    sock->connectToHost(*serverAddr, portno);
    sock->write("hello");
    //qDebug << "I sent hello";
    return 0;
}
int ConnectionClient::waitForResponse(string*){
    return 0;
}
