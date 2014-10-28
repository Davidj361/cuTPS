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
    string *in  = new string();
    string *cmd = new string();

    // Create new ConnectionServer to handle incoming requests
    connection = new ConnectionServer();

    // Create new Serializer to process requests
    // serializer = new Serializer();

    // Create new DBManager to handle all storage operations
    // dbManager = new DBManager();

    while (true) {

        if (!connection->WaitForRequest(in))
            qDebug() << "An error occured while waiting for a request";

        // Deserialize the request
        // if (!serializer->deserialize(in, cmd, /* object out */))
        //    qDebug() << "An error occured while deserializing the request";


        // Handle the command
//        if (cmd == "something") {

//        }
//        else if (cmd == "something else") {

//        }
//        else {
//            qDebug() << "An error occured?";
//        }


        qDebug() << "recieved:" << in->c_str();
        out->assign("dong");

        // Serialize the response
        // if (!serializer->serialize()) {
        //      qDebug() << "An error occured while serializing the response";
        // }

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
