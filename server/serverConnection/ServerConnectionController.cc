#include "ServerConnectionController.h"

using namespace std;

ServerConnectionController::ServerConnectionController (QObject *parent) : QObject(parent) {
    app = QCoreApplication::instance();
    serializer = new ServerSerializer();
}

ServerConnectionController::~ServerConnectionController () {
    delete serializer;
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
        qDebug()<< e.what();
    }

    // Main ServerConnectionController loop
    while (true) {
        try {
            connection->WaitForRequest(in);

            qDebug() << "Received from client...";
            qDebug() << in;
            qDebug() << "Deserializing...";

            QJsonObject objJson;

            command = serializer->deserialize(in, objJson);

            if(command = GET_CONTENT){
                //get content
            }

            else if (command == ADD_TEXTBOOK || command == EDIT_TEXTBOOK || command == REMOVE_TEXTBOOK) {

                Textbook *tb;
                serializer->deserialize(objJson, tb);
                if(command == ADD_TEXTBOOK)
                    // add textbook here
                    1+1;
                if(command == EDIT_TEXTBOOK)
                    //edit here
                    1+1;
                if(command == REMOVE_TEXTBOOK)
                    // remove here
                    1+1;

            }

            else if (command == ADD_CHAPTER || command == EDIT_CHAPTER || command == REMOVE_CHAPTER) {

                Chapter *ch;
                serializer->deserialize(objJson, ch);
                if(command == ADD_CHAPTER)
                    // add textbook here
                    1+1;
                if(command == EDIT_CHAPTER)
                    //edit here
                    1+1;
                if(command == REMOVE_CHAPTER)
                    // remove here
                    1+1;

            }

            else if (command == ADD_SECTION || command == EDIT_SECTION || command == REMOVE_SECTION) {

                Section *s;
                serializer->deserialize(objJson, s);
                if(command == ADD_SECTION)
                    // add textbook here
                    1+1;
                if(command == EDIT_SECTION)
                    //edit here
                    1+1;
                if(command == REMOVE_SECTION)
                    // remove here
                    1+1;

            }

            qDebug() << "Serialized Response...";
            //serializer->Serialize(command, object, (result) ? SUCCESS : ERROR, out);
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
            qDebug() << e.what();

            // On Exception send an error message to the client
            // Don't forget to cleanup!
            if (this->cleanup(command, object))
                throw runtime_error("Couldn't cleanup application");
            QString temp(e.what());
            //serializer->Serialize(command, &temp, ERROR, out);
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
