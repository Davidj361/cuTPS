#include "headers/Controller.h"
#include "../common/headers/User.h"
#include "../common/headers/Student.h"

using namespace std;

Controller::Controller (QObject *parent) : QObject(parent) {
  app = QCoreApplication::instance();
}

Controller::~Controller () {
  delete connection;
}

void Controller::Run () {
  QByteArray *out = new QByteArray();
  QByteArray *in = new QByteArray();
  void *object;
  commands_t command;

  try {
    // Create new ConnectionServer to handle incoming requests
    connection = new ConnectionServer();

    // Create new DBManager to handle all storage operations
    dbManager = new DBManager();
    /* for db management
    Student* u = new Student("admin","pass","Joe Blow");
    dbManager->addUser(u);
    dbManager->addUser(u);
    dbManager->removeUser(u);
    dbManager->removeUser(u);
    */
  }
  catch (exception &e) {
    cout << e.what() << endl;
  }

  // Main controller loop
  while (true) {
    try {
      in = connection->WaitForRequest();
      command = serializer->Deserialize(*in, object);

      switch (command) {
        case ADD_CONTENT:
          // Do something
          break;
        case ADD_INVOICE:
          // Do something
          break;
        case GET_CONTENT:
          // Do something
          break;
      }

      out = serializer->Serialize(command, object, SUCCESS);
      connection->SendResponse(out);
    }
    catch (exception &e) {
      cout << e.what() << endl;
    }
  }

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
