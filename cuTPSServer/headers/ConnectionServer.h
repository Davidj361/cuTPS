#ifndef CONNECTIONSERVER_H
#define CONNECTIONSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

using namespace std;

class ConnectionServer : public QObject{

  public:
    // default port is 60001
    ConnectionServer(QObject *parent = 0);

    /*  IN: int = port  */
    ConnectionServer(int, QObject *parent = 0);

    /*  IN: str* = pointer to json object to be recieved or sent  */
    int waitForRequest(string*);
    int sendResponse(string*);

    ~ConnectionServer();
  private:
    int         portno;
    QTcpServer *server;
    QTcpSocket *sock;


};

#endif
