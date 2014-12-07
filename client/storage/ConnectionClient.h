#ifndef CONNECTIONCLIENT_H
#define CONNECTIONCLIENT_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <stdexcept>
#include <QDataStream>


class ConnectionClient : public QObject {
        Q_OBJECT

    public:
        // default port is 60001
        ConnectionClient(QString *, QObject *parent = 0);

        /* =====================================================================
        Function  : ConnectionClient
        Purpose   : Constructor for ConnectionClient object
        Variables : In  -  IP address as a string
                    In  -  Port to be set
        Returns   : The message received from the client
        ===================================================================== */
        ConnectionClient(QString *, int, QObject *parent = 0);

        ~ConnectionClient();

        /* =====================================================================
        Function  : request
        Purpose   : Sends and recieves messages
        Variables : In  -  Message to be writtern
                    In  -  Message recieved
        Returns   : The message received from the client
        ===================================================================== */
        void request(QByteArray &, QByteArray &);


    private:
        int         portno;
        QString    *serverAddr;
        QTcpSocket *sock;

    public slots:
        void displayNetworkError(QAbstractSocket::SocketError socketError);

    signals:
        void ConnectionError (QString);
};

#endif // CONNECTIONCLIENT_H
