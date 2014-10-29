#ifndef CONNECTIONCLIENT_H
#define CONNECTIONCLIENT_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>

using namespace std;

class ConnectionClient : public QObject {

  public:
    // default port is 60001
    ConnectionClient(QString *, QObject *parent = 0);

    /*  IN: int = port  */
    ConnectionClient(QString *, int, QObject *parent = 0);

    /*  IN: str* = pointer to json object to be recieved or sent  */
    int request(QByteArray *, QByteArray *);


  private:
    int         portno;
    QString    *serverAddr;
    QTcpSocket *sock;



};

#endif // CONNECTIONCLIENT_H
