#include "StorageControl.h"


StorageControl::StorageControl(){

}

StorageControl::~StorageControl(){

}

void StorageControl::addTextbook(Textbook &tb){
    QJsonObject json;
    tb.serialize(json);
    serializer.Serialize(json, ADD_TEXTBOOK);
}

void StorageControl::editTextbook(Textbook &tb){
    QJsonObject json;
    tb.serialize(json);
    serializer.Serialize(json, EDIT_TEXTBOOK);
}

void StorageControl::removeTextbook(Textbook &tb){
    QJsonObject json;
    tb.serialize(json);
    serializer.Serialize(json, REMOVE_TEXTBOOK);
}

void StorageControl::addCourse(Course &c){
    QJsonObject json;
    c.serialize(json);
    serializer.Serialize(json, ADD_COURSE);
}

void StorageControl::editCourse(Course &c){
    QJsonObject json;
    c.serialize(json);
    serializer.Serialize(json, EDIT_COURSE);
}

void StorageControl::removeCourse(Course &c){
    QJsonObject json;
    c.serialize(json);
    serializer.Serialize(json, REMOVE_COURSE);
}

void StorageControl::checkout(Invoice &i){
    QJsonObject json;
    i.serialize(json);
    serializer.Serialize(json, ADD_INVOICE);
}

void StorageControl::refreshContent(User &u, QList<Textbook> &tbs, QList<Course> &cs){
    QJsonObject json;
    u.serialize(json);
    serializer.Serialize(json, GET_CONTENT);
}

