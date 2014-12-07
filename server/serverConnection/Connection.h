#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QThreadPool>
#include "ServerRequestControl.h"
#include <QString>
#include "databaseManagement/DBController.h"

class Connection : public QObject {
    Q_OBJECT

    public:
        explicit Connection( DBController*, QObject *parent = 0);

        void setSocket(qintptr newSock);


    public slots:

        void disconnected();
        void readyRead();
        void response(QByteArray *out);

    private:
        QTcpSocket *sock;
        DBController *db;
};

#endif // CONNECTION_H
