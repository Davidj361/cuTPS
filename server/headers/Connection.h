#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

using namespace std;

class Connection : public QObject{

  public:
    // default port is 60001
    Connection(QObject *parent = 0);

    /*  IN: int = port  */
    Connection(int, QObject *parent = 0);

    /*  IN: str* = pointer to json object to be recieved or sent  */
    int waitForRequest(string*);
    int sendResponse(string*);

    ~Connection();
  private:
    int         portno;
    QTcpServer *server;
    QTcpSocket *sock;


};

#endif
