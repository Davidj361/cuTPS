#ifndef CONNECTIONSERVER_H
#define CONNECTIONSERVER_H

#include <unistd.h>
#include <stdexcept>

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class ConnectionServer : public QObject {

    public:

        // Default port is 60001
        ConnectionServer(QObject *parent = 0);

        // The port number to use
        ConnectionServer(int, QObject *parent = 0);

        ~ConnectionServer();

        /* =====================================================================
        Function  : WaitForRequest
        Purpose   : Waits for and receives a connection from a client
        Variables : In/Out -QByteArray to be written to
        Returns   : The message received from the client
        ===================================================================== */
        void WaitForRequest(QByteArray &);


        /* =====================================================================
        Function  : SendResponse
        Purpose   : Sends a response to a client
        Variables : In - The message being sent to the client
        Returns   : void
        ===================================================================== */
        void SendResponse(QByteArray &);

    public slots:

        void newConnection();

    private:
        int         portno;
        QTcpServer *server;
        QTcpSocket *sock;

};

#endif
