#include "headers/Controller.h"

#define DEBUG
#ifdef DEBUG
#define DEBUG(X) qDebug() << X;
#else
#define DEBUG(X)
#endif

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

      qDebug() << "Variables:";
      qDebug() << "Object*: " << object;

      qDebug() << "Received from client...";
      qDebug() << in;
      qDebug() << "Deserializing...";

      command = serializer->Deserialize(in, object, str1, str2);

      qDebug() << "Done. Passing off to DBManager. Object being sent to DBManager is:";

      QJsonObject json; // For debugging purposes
      switch (command) {
        case ADD_TEXTBOOK:
          (static_cast<Textbook*>(object))->serialize(json);
          qDebug() << json;
          result = dbManager->StoreTextbook(static_cast<Textbook*>(object));
          break;
        case ADD_CHAPTER:
          DEBUG((static_cast<Chapter*>(object))->getTitle())
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
          object = &book_list;
          qDebug() << "We made it out!";
          break;
      }

      qDebug() << "Serialized Response...";
      serializer->Serialize(command, object, (result) ? SUCCESS : ERROR, out);
      qDebug() << "Done. Serialized response is..";
      qDebug() << out;
      connection->SendResponse(out);
      qDebug() << "Response sent";

      // Can't delete a void pointer in C++. Need to cast it so compiler knows which destructor to call
      switch (command) {
        case ADD_TEXTBOOK:
          qDebug() << "Freeing textbook";
          delete (static_cast<Textbook*>(object));
          break;
        case ADD_CHAPTER:
          qDebug() << "Freeing chapter";
          delete (static_cast<Chapter*>(object));
          break;
        case ADD_SECTION:
          qDebug() << "Freeing section";
          delete (static_cast<Section*>(object));
          break;
        case ADD_INVOICE:
          qDebug() << "Freeing invoice";
          delete (static_cast<Invoice*>(object));
          break;
      case GET_CONTENT:
      default:
          break;
      }

      in = 0;
      out = 0;
      object = 0;
    }
    catch (exception &e) {
      cout << e.what() << endl;

      // On Exception send an error message to the client
      serializer->Serialize(command, new QString(e.what()), ERROR, out);
      connection->SendResponse(out);
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
