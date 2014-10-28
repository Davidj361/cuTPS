#include <QApplication>

#include "headers/MainWindow.h"
#include "headers/ConnectionClient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
