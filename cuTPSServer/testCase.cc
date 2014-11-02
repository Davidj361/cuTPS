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
        Serializer serializer;

        // The one below works
        QByteArray arr("{ \"command\": 4, \"status\": 0, \"content\": [ { \"chapters\": [ { \"sections\": [ { \"content\": { \"available\": true, \"title\": \"section 2\", \"sectionNo\": 2, \"description\": \"This is section 2\", \"price\": 10 } } ], \"content\": { \"available\": true, \"price\": 30, \"chapterNo\": 1, \"title\": \"chapter 1\", \"description\": \"This is chapter 1\" } } ], \"content\": { \"available\": true, \"title\":\"playboy\", \"price\": 60, \"author\": \"David\", \"ISBN\": \"01234\", \"publisher\": \"Graehm\", \"description\": \"Boobs\", \"year\": 1991, \"edition\": \"1st\" } } ] }");

        QByteArray arr2("{ \"command\": 4, \"status\": 0, \"content\": [ { \"chapters\": [ { \"sections\": [ { \"content\": { \"available\": true, \"title\": \"section 2\", \"sectionNo\": 2, \"description\": \"This is section 2\", \"price\": 10 } } ], \"content\": { \"available\": true, \"price\": 30, \"chapterNo\": 1, \"title\": \"chapter 1\", \"description\": \"This is chapter 1\" } } ], \"content\": { \"available\": true, \"title\": \"playboy\", \"price\": 60, \"author\": \"David\", \"ISBN\": \"01234\", \"publisher\": \"Graehm\", \"description\": \"Boobs\", \"year\": 1991, \"edition\": \"1st\" } }, { \"chapters\": [ { \"sections\": [ { \"content\": { \"available\": true, \"title\": \"section 2\", \"sectionNo\": 2, \"description\": \"This is section 2\", \"price\": 10 } } ], \"content\": { \"available\": true, \"price\": 30, \"chapterNo\": 1, \"title\": \"chapter 1\", \"description\": \"This is chapter 1\" } } ], \"content\": { \"available\": true, \"title\": \"playboy2\", \"price\": 60, \"author\": \"David\", \"ISBN\": \"01234\", \"publisher\": \"Graehm\", \"description\": \"Boobs\", \"year\": 1991, \"edition\": \"1st\" } }, { \"chapters\": [ { \"sections\": [ { \"content\": { \"available\": true, \"title\": \"section 2\", \"sectionNo\": 2, \"description\": \"This is section 2\", \"price\": 10 } } ], \"content\": { \"available\": true, \"price\": 30, \"chapterNo\": 1, \"title\": \"chapter 1\", \"description\": \"This is chapter 1\" } } ], \"content\": { \"available\": true, \"title\": \"playboy3\", \"price\": 60, \"author\": \"David\", \"ISBN\": \"01234\", \"publisher\": \"Graehm\", \"description\": \"Boobs\", \"year\": 1991, \"edition\": \"1st\" } } ] }");

        vector<Textbook*> textbooks;
        void* temp = 0;
        QString str1, str2;

        try {
        serializer.Deserialize(arr2, temp, str1, str2);
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
