#include <QCoreApplication>

#include "headers/Controller.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    app.applicationName("cuTPS Server");
    app.applicationVersion("0.0.1");
    app.organizationDomain("https://gitlab.com/team-do-not-stick-in-ear/cutps");
    app.organizationName("Team Do Not Stick In Ear");

    Controller *controller = new Controller();

    // connect the signals
    QObject::connect(&controller, SIGNAL(finished()),
             &app, SLOT(quit()));
    QObject::connect(&app, SIGNAL(aboutToQuit()),
             &controller, SLOT(aboutToQuitApp()));

    controller->Run();

    return app.exec();
}
