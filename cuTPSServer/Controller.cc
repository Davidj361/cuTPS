#include "headers/Controller.h"

using namespace std;

Controller::Controller (QObject *parent) : QObject(parent) {
  app = QCoreApplication::instance();
}

Controller::~Controller () {
  delete connection;
}

void Controller::Run () {

  QByteArray out;
  QByteArray in;
  commands_t command;
  void *object;
  QString str1;
  QString str2;

  try {
    // Create new ConnectionServer to handle incoming requests
    connection = new ConnectionServer();

    // Create new DBManager to handle all storage operations
    dbManager = new DBManager();
  }
  catch (exception &e) {
    cout << e.what() << endl;
  }

  // Main controller loop
  while (true) {
    try {
      connection->WaitForRequest(in);
      qDebug() << "LOOK OUT!";
      qDebug() << in;
      command = serializer->Deserialize(in, object, str1, str2);

      switch (command) {
        case ADD_TEXTBOOK:
          // Do something
          break;
        case ADD_CHAPTER:
          // Do something
          break;
        case ADD_SECTION:
          // Do something
          break;
        case ADD_INVOICE:
          // Do something
          break;
        case GET_CONTENT:
          // Do something
          break;
      }

      serializer->Serialize(command, object, SUCCESS, out);
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
