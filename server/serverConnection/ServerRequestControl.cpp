#include "ServerRequestControl.h"

using namespace std;

ServerRequestControl::ServerRequestControl( QByteArray *bytes , DBController* cDb) {

    // set the in message
    in = bytes;
    db = cDb;

}

ServerRequestControl::~ServerRequestControl() {
    if(in != 0)
        delete in;
}

void ServerRequestControl::run(){

    // set up variables
    QByteArray *out = new QByteArray();
    commands_t command;
    ServerSerializer *serializer = new ServerSerializer();

    try {

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
            if(user != 0)
                delete user;

        }


        else if ( command == ADD_TEXTBOOK ) {

            Class *cl;
            serializer->deserialize(objJson, cl);

            foreach (Textbook *textbook, cl->getBooklist()) {
                db->AddTextbook(textbook);
            }

            db->AddTextbooksToClass(cl);
            if(cl->getCourse() == 0)
                delete cl->getCourse();
            if(cl != 0)
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

            if(tb != 0)
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

            if(ch->getTextbook() != 0)
                delete ch->getTextbook();
            if(ch != 0)
                delete ch;

            serializer->serializeSuccess(command, *out);

        }

        else if ( command == ADD_SECTION || command == EDIT_SECTION || command == REMOVE_SECTION ) {

            Section *s;
            serializer->deserialize(objJson, s);

            if(command == ADD_SECTION)
                db->AddSection(s);

            if(command == EDIT_SECTION)
                db->EditSection(s);

            if(command == REMOVE_SECTION)
                db->DeleteSection(s);
            if(s->getChapter() !=0)
                delete s->getChapter();
            if(s->getTextbook() != 0)
                delete s->getTextbook();
            if(s != 0)
                delete s;

            serializer->serializeSuccess(command, *out);

        }

        else if ( command == LOGIN ){

            User *user;
            serializer->deserialize(objJson, user);

            db->Login(user);

            serializer->serializeUser(*user, LOGIN, *out);

            if(user != 0)
                delete user;

        }


        else if (command == REMOVE_COURSE){

            Course *course;
            serializer->deserializeCourse(objJson, course);

            db->DeleteCourse(course);

            if(course != 0)
                delete course;

            serializer->serializeSuccess(command, *out);

        }

        else if( command == ADD_CLASS || command == DELETE_CLASS ){

            Class *cl;
            serializer->deserialize(objJson, cl);

            if ( command == ADD_CLASS ){
                if(!db->CourseExists(cl->getCourse()))
                    db->AddCourse(cl->getCourse());
                db->AddClass(cl);
            }

            if ( command == DELETE_CLASS)
                db->DeleteClass(cl);

            serializer->serializeSuccess(command, *out);

            if(cl->getCourse() != 0)
                delete cl->getCourse();
            if(cl != 0)
                delete cl;

        }

        else if( command == ADD_INVOICE ) {

            Invoice *i;
            serializer->deserialize(objJson, i);

            db->AddInvoice(i);

            if(i != 0)
                delete i;

            serializer->serializeSuccess(command, *out);

        }

        emit response(out);

    } catch ( exception &e ) {

        qDebug() << e.what();

        QString temp(e.what());
        serializer->serializeError(temp, command, *out);

        emit response(out);

    }

}
