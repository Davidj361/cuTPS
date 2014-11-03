#include <iostream>
#include <vector>
#include <stdexcept>

#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QDebug>

#include "../common/headers/Serializer.h"
#include "../common/headers/Textbook.h"

using namespace std;

int main() {

        ///////////////////////////////////////////////////////////
        // COPY PASTE FROM MainWindow.cpp

        Serializer* serializer = new Serializer;
        void* object = 0;
        QByteArray req, res;
        QString result, errorMsg;

        Textbook *t = new Textbook("1234567890", "Learning NodeJS", "David J", "Graeme J", 2014, "1", "Everything you need to know about NodeJS", true, 50);
        Chapter  *c = new Chapter("V8 Engine", 1, t, "More horsepower!", true, 15);
        Section  *s = new Section("Many ponies", 1, c, t, "Ponies are funny looking", true, 5);

        serializer->Serialize(ADD_TEXTBOOK, t, REQUEST, req);
        serializer->Deserialize(req, object, result, errorMsg);
        qDebug() << "Textbook deserialized";
        t = static_cast<Textbook*>(object);
        qDebug() << t->getTitle();
        object = 0;

        serializer->Serialize(ADD_CHAPTER, c, REQUEST, req);
        serializer->Deserialize(req, object, result, errorMsg);
        qDebug() << "Chapter deserialized";
        c = static_cast<Chapter*>(object);
        qDebug() << c->getTitle();
        object = 0;

        serializer->Serialize(ADD_SECTION, s, REQUEST, req);
        serializer->Deserialize(req, object, result, errorMsg);
        qDebug() << "Section deserialized";
        s = static_cast<Section*>(object);
        qDebug() << s->getTitle();
        object = 0;
        
        // END OF COPY PASTE FROM MainWindow.cpp
        ///////////////////////////////////////////////////

        QByteArray arr("{ \"command\": 4, \"status\": 0, \"content\": [ { \"chapters\": [ { \"sections\": [ { \"content\": { \"available\": true, \"title\": \"section 2\", \"sectionNo\": 2, \"description\": \"This is section 2\", \"price\": 10 } } ], \"content\": { \"available\": true, \"price\": 30, \"chapterNo\": 1, \"title\": \"chapter 1\", \"description\": \"This is chapter 1\" } } ], \"content\": { \"available\": true, \"title\":\"playboy\", \"price\": 60, \"author\": \"David\", \"ISBN\": \"01234\", \"publisher\": \"Graehm\", \"description\": \"Boobs\", \"year\": 1991, \"edition\": \"1st\" } } ] }");

        QByteArray arr2("{ \"command\": 4, \"status\": 0, \"content\": [ { \"chapters\": [ { \"sections\": [ { \"content\": { \"available\": true, \"title\": \"section 2\", \"sectionNo\": 2, \"description\": \"This is section 2\", \"price\": 10 } } ], \"content\": { \"available\": true, \"price\": 30, \"chapterNo\": 1, \"title\": \"chapter 1\", \"description\": \"This is chapter 1\" } } ], \"content\": { \"available\": true, \"title\": \"playboy\", \"price\": 60, \"author\": \"David\", \"ISBN\": \"01234\", \"publisher\": \"Graehm\", \"description\": \"Boobs\", \"year\": 1991, \"edition\": \"1st\" } }, { \"chapters\": [ { \"sections\": [ { \"content\": { \"available\": true, \"title\": \"section 2\", \"sectionNo\": 2, \"description\": \"This is section 2\", \"price\": 10 } } ], \"content\": { \"available\": true, \"price\": 30, \"chapterNo\": 1, \"title\": \"chapter 1\", \"description\": \"This is chapter 1\" } } ], \"content\": { \"available\": true, \"title\": \"playboy2\", \"price\": 60, \"author\": \"David\", \"ISBN\": \"01234\", \"publisher\": \"Graehm\", \"description\": \"Boobs\", \"year\": 1991, \"edition\": \"1st\" } }, { \"chapters\": [ { \"sections\": [ { \"content\": { \"available\": true, \"title\": \"section 2\", \"sectionNo\": 2, \"description\": \"This is section 2\", \"price\": 10 } } ], \"content\": { \"available\": true, \"price\": 30, \"chapterNo\": 1, \"title\": \"chapter 1\", \"description\": \"This is chapter 1\" } } ], \"content\": { \"available\": true, \"title\": \"playboy3\", \"price\": 60, \"author\": \"David\", \"ISBN\": \"01234\", \"publisher\": \"Graehm\", \"description\": \"Boobs\", \"year\": 1991, \"edition\": \"1st\" } } ] }");

        Serializer serializer2;
        vector<Textbook*> textbooks;
        void* temp = 0;
        QString str1, str2;

        try {
                serializer2.Deserialize(arr, temp, str1, str2);
        } catch (exception& e) {
                cout << e.what() << endl;
        }
        textbooks = *(static_cast<vector<Textbook*>*>(temp));
        qDebug() << textbooks.at(0)->getTitle();

        temp = 0;
        try {
                serializer2.Deserialize(arr2, temp, str1, str2);
        } catch (exception& e) {
                cout << e.what() << endl;
        }
        textbooks = *(static_cast<vector<Textbook*>*>(temp));
        qDebug() << textbooks.at(0)->getTitle();
        qDebug() << textbooks.at(1)->getTitle();
        qDebug() << textbooks.at(2)->getTitle();
        cout << "works" << endl;
        return 0;
}
