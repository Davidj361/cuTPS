#include "ServerConnectionController.h"

using namespace std;

ServerConnectionController::ServerConnectionController (QObject *parent) : QObject(parent) {
    app = QCoreApplication::instance();
}

ServerConnectionController::~ServerConnectionController () {
}

void ServerConnectionController::Run () {
    QByteArray in;
    QByteArray out;
    commands_t command;
    QString str1;
    QString str2;
    void *object = 0;
    vector<Textbook *> book_list;
    bool result;

    try {
        // Create new ConnectionServer to handle incoming requests
        connection = new ConnectionServer();

        // Create new dbController to handle all storage operations
        dbController = new DBController();
    }
    catch (exception &e) {
        cout << e.what() << endl;
    }

    // Main ServerConnectionController loop
    while (true) {
        try {
            connection->WaitForRequest(in);

            qDebug() << "Received from client...";
            qDebug() << in;
            qDebug() << "Deserializing...";

            command = serializer->Deserialize(in, object, str1, str2);

            qDebug() << "Done. Passing off to dbController. Object being sent to dbController is:";

            QJsonObject json; // For debugging purposes
            switch (command) {
                case ADD_TEXTBOOK:
                    (static_cast<Textbook *>(object))->serialize(json);
                    qDebug() << json;
                    dbController->StoreTextbook(static_cast<Textbook *>(object));
                    result = true;
                    break;
                case ADD_CHAPTER:
                    (static_cast<Chapter *>(object))->serialize(json);
                    qDebug() << json;
                    result = dbController->StoreChapter(static_cast<Chapter *>(object), str1);
                    break;
                case ADD_SECTION:
                    (static_cast<Section *>(object))->serialize(json);
                    qDebug() << json;
                    result = dbController->StoreSection(static_cast<Section *>(object), str1, str2);
                    break;
                case ADD_INVOICE:
                    (static_cast<Invoice *>(object))->serialize(json);
                    qDebug() << json;
                    result = dbController->StoreInvoice(static_cast<Invoice *>(object));
                    break;
                case GET_CONTENT:
                    result = dbController->RetrieveContentList(str1, book_list);
                    object = &book_list;
                    break;
            }

            qDebug() << "Serialized Response...";
            serializer->Serialize(command, object, (result) ? SUCCESS : ERROR, out);
            qDebug() << "Done. Serialized response size is.." << out.size();
            connection->SendResponse(out);
            qDebug() << "Response sent";

            // cleanup the object
            if (this->cleanup(command, object))
                throw runtime_error("Couldn't cleanup application");


            in = 0;
            out = 0;
            object = 0;
        }
        catch (exception &e) {
            cout << e.what() << endl;

            // On Exception send an error message to the client
            // Don't forget to cleanup!
            if (this->cleanup(command, object))
                throw runtime_error("Couldn't cleanup application");
            QString temp(e.what());
            serializer->Serialize(command, &temp, ERROR, out);
            connection->SendResponse(out);
            object = 0;
        }
    }
    Quit();
}

void ServerConnectionController::Quit() {
    // you can do some cleanup here
    // then do emit finished to signal CoreApplication to quit
    qDebug() << "Emitting the finished signal";
    emit Finished();
}

// shortly after quit is called the CoreApplication will signal this routine
// this is a good place to delete any objects that were created in the
// constructor and/or to stop any threads
void ServerConnectionController::AboutToQuitApp() {
    delete connection;
    delete dbController;
    delete app;
    qDebug() << "In ServerConnectionController::AboutToQuitApp";
}

int ServerConnectionController::cleanup(commands_t command, void *&object) {
    if (object == 0)
        return 0;
    // Can't delete a void pointer in C++. Need to cast it so compiler knows which destructor to call
    vector<Textbook *> *book_list;
    switch (command) {
        case ADD_TEXTBOOK:
            qDebug() << "Freeing textbook";
            delete (static_cast<Textbook *>(object));
            break;
        case ADD_CHAPTER:
            qDebug() << "Freeing chapter";
            delete (static_cast<Chapter *>(object));
            break;
        case ADD_SECTION:
            qDebug() << "Freeing section";
            delete (static_cast<Section *>(object));
            break;
        case ADD_INVOICE:
            qDebug() << "Freeing invoice";
            delete (static_cast<Invoice *>(object));
            break;
        case GET_CONTENT:
            qDebug() << "Freeing content list";
            book_list = static_cast<vector<Textbook *>*>(object);
            for (vector<Textbook *>::iterator it = book_list->begin(); it != book_list->end(); ++it) {
                if ( (*it) != 0) {
                    delete *it;
                    (*it) = 0;
                }
            }
            book_list->clear();
            break;
        default:
            return 1;
    }
    return 0;
}
