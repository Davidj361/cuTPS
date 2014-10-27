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

void Controller::Run () {
    string *out = new string();
    string *in = new string();

    // Create new ConnectionServer to handle incoming requests
    connection = new ConnectionServer();

    while (true) {

        if (!connection->WaitForRequest(in))
            qDebug() << "An error occured while waiting for a request";

        qDebug() << "recieved:" << in->c_str();
        out->assign("dong");

        connection->SendResponse(out);
    }

    // you must call quit when complete or the program will stay in the
    // messaging loop
    Quit();
}

void Controller::Quit() {
    // you can do some cleanup here
    // then do emit finished to signal CoreApplication to quit
    qDebug() << "Emitting the finished signal";
    emit Finished();
}

// shortly after quit is called the CoreApplication will signal this routine
// this is a good place to delete any objects that were created in the
// constructor and/or to stop any threads
void Controller::AboutToQuitApp() {
    // stop threads
    // sleep(1);   // wait for threads to stop.
    // delete any objects
    qDebug() << "In Controller::AboutToQuitApp";
}
