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

        QByteArray arr("{\"command\":4,\"content\":[{\"title\":\"Playboy\",\"available\":true,\"price\":60,\"author\":\"David\",\"ISBN\":\"01234\",\"publisher\":\"Graehm\",\"edition\":\"1st\",\"description\":\"Boobs\",\"year\":1991,\"chapters\":[{\"title\":\"chapter 1\",\"available\":true,\"price\":30,\"chapterNo\":1,\"description\":\"This is chapter 1\",\"sections\":[{\"title\":\"section 2\",\"available\":true,\"price\":10,\"sectionNo\":2,\"description\":\"This is section 2\"}]}]}]}");

        //QJsonObject json = QJsonDocument::fromJson(arr).object();

        vector<Textbook*> textbooks;
        void* temp = 0;
        QString str1, str2;

        try {
        serializer.Deserialize(arr, temp, str1, str2);
        } catch (exception& e) {
                cout << e.what() << endl;
        }
        textbooks = *(static_cast<vector<Textbook*>*>(temp));
        qDebug() << textbooks.at(0)->getTitle();
        cout << "works" << endl;
        return 0;
}
