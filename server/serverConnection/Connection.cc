#include "Connection.h"


Connection::Connection(DBController *cDb, QObject *parent) :
    QObject(parent)
{

    // Set amount of threads that can run concurrently
    QThreadPool::globalInstance()->setMaxThreadCount(4);
    db = cDb;

}

Connection::~Connection(){
    delete sock;
}

void Connection::setSocket ( qintptr newSock ) {

    // New tcpsocket
    sock = new QTcpSocket(this);

    // connect signals
    connect(sock, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(readyRead()));

    // set the socket
    sock->setSocketDescriptor(newSock);

}


void Connection::disconnected() {

    qDebug() << "Client disconnected";

}

void Connection::readyRead() {

    // read the message from the socket
    QByteArray *str = new QByteArray(sock->readAll());

    // Runnable that contains main functionality
    ServerRequestControl* src = new ServerRequestControl(str, db);
    src->setAutoDelete(true);

    // Connects result with function to send it
    connect(src, SIGNAL(response(QByteArray*)), this, SLOT(response(QByteArray*)), Qt::QueuedConnection);

    // Start the runnable
    QThreadPool::globalInstance()->start(src);

}

void Connection::response(QByteArray *out) {

    // Turn size of message into QByteArray
    QString outSize = QString::number(out->size());
    QByteArray outSizearr;
    outSizearr.append(outSize+'\n');

    // Send the size
    sock->write(outSizearr);

    // Send the message
    sock->write(*out);

}
