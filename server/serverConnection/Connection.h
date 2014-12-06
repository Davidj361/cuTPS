#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QThreadPool>
#include "ServerRequestControl.h"
#include <QString>

class Connection : public QObject {
    Q_OBJECT

    public:
        explicit Connection(QObject *parent = 0);

        void setSocket(qintptr newSock);


    public slots:

        void disconnected();
        void readyRead();
        void response(QByteArray *out);

    private:
        QTcpSocket *sock;
};

#endif // CONNECTION_H
