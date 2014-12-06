#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include "Connection.h"
#include <stdexcept>

using namespace std;

class Server : public QTcpServer {
    Q_OBJECT

    public:
        explicit Server(QObject *parent = 0);
        void start(int port = 60001);

    protected:
        void incomingConnection(qintptr sock);

    private:
        int portno;

};

#endif // SERVER_H
