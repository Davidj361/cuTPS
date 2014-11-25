#include "headers/Course.h"

Course::Course(QString courseTitle, QString courseCode, QString term){
    this->courseCode = courseCode;
    this->courseTitle = courseTitle;
    this->term = term;
    textbooks = new QList();
}
Course::~Course(){
    // TODO Delete textbooks?
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

QList<Textbook> Course::getTextbooks(){
    return textbooks;
 }

void Course::addTextbook(Textbook tb){
    textbooks.append(tb);
}

void Course::removeTextbook(Textbook tb){
    textbooks.removeOne(tb);
}

