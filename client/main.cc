#include <QApplication>

#include "contentDisplay/ui/MainWindow.h"
#include "storage/ConnectionClient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
