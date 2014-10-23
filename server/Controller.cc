#include <QDebug>

#include "headers/Controller.h"

using namespace std;

Controller::Controller (QObject *parent) : QObject(parent) {
    app = QCoreApplication::instance();

    // setup everything here
    // create any global objects
    // setup debug and warning mode
}

Controller::~Controller () {
}

int Controller::Run () {
    qDebug() << "MainClass.Run is executing";

    // you must call quit when complete or the program will stay in the
    // messaging loop
    Quit();
}

void Controller::Quit() {
    // you can do some cleanup here
    // then do emit finished to signal CoreApplication to quit
    emit Finished();
}

// shortly after quit is called the CoreApplication will signal this routine
// this is a good place to delete any objects that were created in the
// constructor and/or to stop any threads
void Controller::AboutToQuitApp() {
    // stop threads
    // sleep(1);   // wait for threads to stop.
    // delete any objects
}
