#include <QCoreApplication>
#include <QTimer>
#include "serverConnection/Server.h"


using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    app.setApplicationName("cuTPS Server");
    app.setApplicationVersion("0.0.1");
    app.setOrganizationDomain("https://gitlab.com/team-do-not-stick-in-ear/cutps");
    app.setOrganizationName("Team Do Not Stick In Ear");

    DBController db;

    // Start the server
    Server server(&db);
    try {
        server.start();
        return app.exec();
    }
    catch(std::runtime_error e) {
        qDebug() << e.what();
    }
}
