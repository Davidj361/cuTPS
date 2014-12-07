#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include "Connection.h"
#include <stdexcept>
#include "databaseManagement/DBController.h"

using namespace std;

class Server : public QTcpServer {
    Q_OBJECT

    public:
        explicit Server(DBController *, QObject *parent = 0);
        void start(int port = 60001);

    protected:
        void incomingConnection(qintptr sock);

    private:
        int portno;
        DBController *db;

};

#endif // SERVER_H
