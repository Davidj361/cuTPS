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
    server.start();

    /* TODO is this still needed?
    // connect the signals
    QObject::connect(controller, SIGNAL(Finished()),
                     &app, SLOT(quit()));

    QObject::connect(&app, SIGNAL(aboutToQuit()),
                     controller, SLOT(AboutToQuitApp()));

    QTimer::singleShot(10, controller, SLOT(Run()));*/

    return app.exec();
}
