#include "headers/mainwindow.h"
#include <QApplication>
#include "headers/ConnectionClient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    string* ip = new string("127.0.0.1");
    ConnectionClient *connection;
    connection =new ConnectionClient(ip,60001);

    string *out = new string();
    string *in = new string("ding");
    connection->request(in,out);
    qDebug()<<out->c_str();
    w.show();

    return a.exec();
}
