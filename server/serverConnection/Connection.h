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

        /* =====================================================================
        Function  : setSocket
        Purpose   : Set the connections socket
        Variables : IN  -  qintptr, socket int
        Returns   : void
        ===================================================================== */
        void setSocket(qintptr newSock);


    public slots:

        /* =====================================================================
        Function  : disconnected
        Purpose   : Catch the signal from the socket that it has disconnected
        Returns   : void
        ===================================================================== */
        void disconnected();

        /* =========================================================================
        Function  : readyRead
        Purpose   : Catch the signal from the socket that it has information to read
                    creates creates a thread and passes the read message to it to do
                    the work
        Returns   : void
        =========================================================================== */
        void readyRead();

        /* =========================================================================
        Function  : response
        Purpose   : Catch the signal from the work thread that contains the response
        Variables : IN - message to be sent back to client
        Returns   : void
        =========================================================================== */
        void response(QByteArray *out);

    private:

        QTcpSocket *sock;
        DBController *db;

};

#endif // CONNECTION_H
