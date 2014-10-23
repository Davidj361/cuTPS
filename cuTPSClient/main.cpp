#include "headers/mainwindow.h"
#include <QApplication>
#include "headers/ConnectionClient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    string* ip = new string("192.132.242.2");
    ConnectionClient *connection;
    connection =new ConnectionClient(ip,1234);
    connection->sendRequest(ip);
    w.show();

    return a.exec();
}
