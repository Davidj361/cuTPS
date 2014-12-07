#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include "Connection.h"
#include <stdexcept>
#include "databaseManagement/DBController.h"

class Server : public QTcpServer {
    Q_OBJECT

    public:
        explicit Server(DBController *, QObject *parent = 0);

        /* =========================================================================
        Function  : start
        Purpose   : start the server listening for connections
        Variables : IN  -  Takes a port, defaults to 60001
        Returns   : void
        =========================================================================== */
        void start(int port = 60001);

    protected:

        /* =========================================================================
        Function  : incommingConnection
        Purpose   : Signal called when a connection is made
        Variables : IN  -  sock, is a socket
        Returns   : void
        =========================================================================== */
        void incomingConnection(qintptr sock);

    private:
        int portno;
        DBController *db;

};

#endif // SERVER_H
