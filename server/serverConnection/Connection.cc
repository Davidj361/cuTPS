#include "Connection.h"


Connection::Connection(DBController *cDb, QObject *parent) :
    QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(4);
    db = cDb;
}

void Connection::setSocket ( qintptr newSock ) {

    sock = new QTcpSocket(this);

   // connect(sock, SIGNAL(connected()), this, SLOT(connected()));
    connect(sock, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(readyRead()));

    sock->setSocketDescriptor(newSock);

}


void Connection::disconnected()
{
    qDebug() << "Client disconnected";
}

void Connection::readyRead()
{
    qDebug() << "Connection::readyRead()";

    QByteArray *str = new QByteArray(sock->readAll());

    // Runnable that contains main functionality
    ServerRequestControl *src = new ServerRequestControl(str, db);
    src->setAutoDelete(true);

    // Connects result with function to send it
    connect(src, SIGNAL(response(QByteArray*)), this, SLOT(response(QByteArray*)), Qt::QueuedConnection);

    // Start the runnable
    QThreadPool::globalInstance()->start(src);

}

void Connection::response(QByteArray *out)
{
    // Turn size of message into QByteArray
    QString outSize = QString::number(out->size());
    QByteArray outSizearr;
    outSizearr.append(outSize+'\n');
    qDebug() << outSize;

    // Send the size
    sock->write(outSizearr);

    // Send the message
    sock->write(*out);
}
