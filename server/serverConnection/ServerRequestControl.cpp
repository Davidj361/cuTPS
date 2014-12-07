#include "ServerRequestControl.h"

using namespace std;

ServerRequestControl::ServerRequestControl( QByteArray *bytes , DBController* cDb) {

    // set the in message
    in = bytes;
    db = cDb;

}

ServerRequestControl::~ServerRequestControl() {
    delete in;
}

void ServerRequestControl::run(){

    // set up variables
    QByteArray *out = new QByteArray();
    commands_t command;
    DBController *db = new DBController();
    ServerSerializer *serializer = new ServerSerializer();

    try {

        qDebug() << "Deserializing...";

        QJsonObject objJson;

        //decouple command from the json
        command = serializer->deserialize(*in, objJson);

        // for each of these if statements, the json is deserialized,
        // the db queried, and the response generated
        if ( command == GET_CONTENT ){

            User* user;
            serializer->deserialize(objJson, user);

            QList<Class *> list;
            QString username = user->getUsername();

            db->RetrieveContentList(username, list);

            serializer->serializeClasses(list, command, *out);

            delete user;

        }


        else if ( command == ADD_TEXTBOOK ) {

            Class *cl;
            serializer->deserialize(objJson, cl);

            db->AddTextbooksToClass(cl);

            delete cl;

            serializer->serializeSuccess(command, *out);

        }

        else if ( command == EDIT_TEXTBOOK || command == REMOVE_TEXTBOOK ){
            Textbook *tb;

            serializer->deserialize(objJson, tb);

            if(command == EDIT_TEXTBOOK)
                db->EditTextbook(tb);

            if(command == REMOVE_TEXTBOOK)
                db->DeleteTextbook(tb);

            delete tb;

            serializer->serializeSuccess(command, *out);

        }

        else if ( command == ADD_CHAPTER || command == EDIT_CHAPTER || command == REMOVE_CHAPTER ) {

            Chapter *ch;
            serializer->deserialize(objJson, ch);

            if(command == ADD_CHAPTER)
                db->AddChapter(ch);

            if(command == EDIT_CHAPTER)
                db->EditChapter(ch);

            if(command == REMOVE_CHAPTER)
                db->DeleteChapter(ch);

            delete ch;

            serializer->serializeSuccess(command, *out);

        }

        else if ( command == ADD_SECTION || command == EDIT_SECTION || command == REMOVE_SECTION ) {

            Section *s;
            serializer->deserialize(objJson, s);

            if(command == ADD_SECTION)
                db->AddSection(s);

            if(command == ADD_CLASS)
                db->EditSection(s);

            if(command == REMOVE_SECTION)
                db->DeleteSection(s);

            delete s;

            serializer->serializeSuccess(command, *out);

        }

        else if ( command == LOGIN ){

            User *user;
            serializer->deserialize(objJson, user);

            db->Login(user);

            serializer->serializeUser(*user, LOGIN, *out);

            delete user;

        }


        else if (command == REMOVE_COURSE){

            Course *course;
            serializer->deserializeCourse(objJson, course);

            db->DeleteCourse(course);

            delete course;

            serializer->serializeSuccess(command, *out);

        }

        else if( command == ADD_CLASS || command == DELETE_CLASS ){

            Class *cl;
            serializer->deserialize(objJson, cl);

            if ( command == ADD_CLASS )
                db->AddClass(cl);

            if ( command == DELETE_CLASS)
                db->DeleteClass(cl);

            serializer->serializeSuccess(command, *out);

        }

        else if( command == ADD_INVOICE ) {

            Invoice *i;
            serializer->deserialize(objJson, i);

            db->AddInvoice(i);

            delete i;

            serializer->serializeSuccess(command, *out);

        }


        qDebug() << "Serialized Response...";
        qDebug() << *out;
        qDebug() << "Done.  Serialized response size is.." << out->size();
        emit response(out);
        qDebug() << "Response sent";

    } catch ( exception &e ) {

        qDebug() << e.what();

        QString temp(e.what());
        serializer->serializeError(temp, command, *out);

        emit response(out);

    }

}
