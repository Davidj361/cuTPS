#include <QCoreApplication>
#include <QTimer>

#include "headers/Controller.h"

using namespace std;

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  app.setApplicationName("cuTPS Server");
  app.setApplicationVersion("0.0.1");
  app.setOrganizationDomain("https://gitlab.com/team-do-not-stick-in-ear/cutps");
  app.setOrganizationName("Team Do Not Stick In Ear");

  Controller *controller = new Controller();

  // connect the signals
  QObject::connect(controller, SIGNAL(Finished()),
                   &app, SLOT(quit()));

  QObject::connect(&app, SIGNAL(aboutToQuit()),
                   controller, SLOT(AboutToQuitApp()));

  QTimer::singleShot(10, controller, SLOT(Run()));

  return app.exec();
}
