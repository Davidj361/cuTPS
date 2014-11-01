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
  vector<Textbook> book_list;
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
      qDebug() << "Received from client...";
      qDebug() << in;
      command = serializer->Deserialize(in, object, str1, str2);
      qDebug() << "Deserialized into...";
      qDebug() << "Str1 - " << str1;
      qDebug() << "Str2 - " << str2;
      QJsonObject json;
      switch (command) {
        case ADD_TEXTBOOK:
          (static_cast<Textbook*>(object))->serialize(json);
          qDebug() << json;
          result = dbManager->StoreTextbook(static_cast<Textbook*>(object));
          break;
        case ADD_CHAPTER:
          (static_cast<Chapter*>(object))->serialize(json);
          qDebug() << json;
          result = dbManager->StoreChapter(static_cast<Chapter*>(object), str1);
          break;
        case ADD_SECTION:
          (static_cast<Section*>(object))->serialize(json);
          qDebug() << json;
          result = dbManager->StoreSection(static_cast<Section*>(object), str1, str2);
          break;
        case ADD_INVOICE:
          (static_cast<Invoice*>(object))->serialize(json);
          qDebug() << json;
          result = dbManager->StoreInvoice(static_cast<Invoice*>(object));
          break;
        case GET_CONTENT:
          result = dbManager->RetrieveContentList(str1, book_list);
          qDebug() << "We made it out!";
          break;
      }

      serializer->Serialize(command, object, (result) ? SUCCESS : ERROR, out);
      qDebug() << "Serialized Response...";
      qDebug() << out;
      connection->SendResponse(out);

      delete object;
      object = 0;
    }
    catch (exception &e) {
      cout << e.what() << endl;
      // On Exception send an error message to the client
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
