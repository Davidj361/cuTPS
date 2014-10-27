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

    ~ConnectionServer();

    /* =====================================================================
    Function  : WaitForRequest
    Purpose   : Waits for and receives a connection from a client
    Variables : Out - string* - The message received from the client
    Returns   : 1 - Success
                0 - Fail
    ===================================================================== */
    int WaitForRequest(string*);

    /* =====================================================================
    Function  : SendResponse
    Purpose   : Sends a response to a client
    Variables : In - string* - The message sent to the client
    Returns   : 1 - Success
                0 - Fail
    ===================================================================== */
    int SendResponse(string*);
  private:
    int         portno;
    QTcpServer *server;
    QTcpSocket *sock;


};

#endif
