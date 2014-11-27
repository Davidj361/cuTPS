#include "headers/Course.h"

Course::Course(QString courseTitle, QString courseCode, QString term){
    this->courseCode = courseCode;
    this->courseTitle = courseTitle;
    this->term = term;
}
void Course::serialize(QJsonObject &json){
    json.insert("courseCode", courseCode);
    json.insert("courseTitle", courseTitle);
    json.insert("term", term);
    QJsonArray textbooksJson;
        QJsonObject tJson;
        textbooksJson.append(tJson);
    }
    json.insert("textbooks", textbooksJson);
}

Course::~Course() {
        for (QList<Textbook*>::iterator iter = this->textbooks.begin(); iter != this->textbooks.end(); ++iter) {
                delete *iter;
                *iter = 0;
        }
}

QString Course::getCourseTitle(){
    return courseTitle;
}

QString Course::getCourseCode(){
    return courseCode;
}

QString Course::getTerm(){
    return term;
}

QList<Textbook*> Course::getTextbooks(){
    return textbooks;
 }

void Course::addTextbook(Textbook* tb){
    textbooks.append(tb);
}

void Course::removeTextbook(Textbook tb){
    // TODO textbooks need operator== overwritten
    //textbooks.removeOne(tb);
}

