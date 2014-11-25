#include "StorageControl.h"


StorageControl::StorageControl(){

}

StorageControl::~StorageControl(){

}

void StorageControl::addTextbook(Textbook &tb){
    QJsonObject request;
    serializer.Serialize(tb, ADD_TEXTBOOK, request);
}

void StorageControl::editTextbook(Textbook &tb){
    QJsonObject request;
    serializer.Serialize(tb, EDIT_TEXTBOOK, request);
}

void StorageControl::removeTextbook(Textbook &tb){
    QJsonObject request;
    serializer.Serialize(tb, REMOVE_TEXTBOOK, request);
}

void StorageControl::addCourse(Course &c){
    QJsonObject request;
    serializer.Serialize(c, ADD_COURSE, request);
}

void StorageControl::editCourse(Course &c){
    QJsonObject request;
    serializer.Serialize(c, EDIT_COURSE, request);
}

void StorageControl::removeCourse(Course &c){
    QJsonObject request;
    serializer.Serialize(c, REMOVE_COURSE, request);
}

void StorageControl::checkout(Invoice &i){
    QJsonObject request;
    serializer.Serialize(i, ADD_INVOICE, request);
}

void StorageControl::refreshContent(User &u, QList<Textbook> &tbs, QList<Course> &cs){
    QJsonObject request;
    serializer.Serialize(u, GET_CONTENT, request);
}

