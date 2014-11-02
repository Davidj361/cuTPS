#ifndef CONNECTIONCLIENT_H
#define CONNECTIONCLIENT_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>

using namespace std;

class ConnectionClient : public QObject {
    Q_OBJECT

  public:
    // default port is 60001
    ConnectionClient(QString *, QObject *parent = 0);

    /*  IN: int = port  */
    ConnectionClient(QString *, int, QObject *parent = 0);

    /*  IN: str* = pointer to json object to be recieved or sent  */
    void request(QByteArray&, QByteArray&);


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
