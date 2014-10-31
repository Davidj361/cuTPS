#include "headers/Controller.h"

using namespace std;

Controller::Controller (QObject *parent) : QObject(parent) {
  app = QCoreApplication::instance();
}

Controller::~Controller () {
  delete connection;
  delete dbManager;
  // delete app; ?
}

void Controller::Run () {

  QByteArray in;
  QByteArray out;
  commands_t command;
  QString str1;
  QString str2;
  void *object = 0;
  bool result;

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
      command = serializer->Deserialize(in, object, str1, str2);

      switch (command) {
        case ADD_TEXTBOOK:
          result = dbManager->StoreTextbook(static_cast<Textbook*>(object));
          break;
        case ADD_CHAPTER:
          result = dbManager->StoreChapter(static_cast<Chapter*>(object), str1);
          break;
        case ADD_SECTION:
          result = dbManager->StoreSection(static_cast<Section*>(object), str1, str2);
          break;
        case ADD_INVOICE:
          result = dbManager->StoreInvoice(static_cast<Invoice*>(object));
          break;
        case GET_CONTENT:
          break;
      }

      serializer->Serialize(command, object, SUCCESS, out);
      connection->SendResponse(out);

      delete object;
      object = 0;
    }
    catch (exception &e) {
      cout << e.what() << endl;
      delete object;
      object = 0;
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
