#include "StorageControl.h"


StorageControl::StorageControl(){
    // TODO figure out how to retrieve ip
    QString ip = "127.0.0.1";
    connection = new ConnectionClient(&ip);
    serializer = new ClientSerializer();
}

StorageControl::~StorageControl(){
    delete connection;
    delete serializer;
}

void StorageControl::addTextbook(Textbook &tb){
    updateStorage(tb, ADD_TEXTBOOK);
}

void StorageControl::editTextbook(Textbook &tb){
    updateStorage(tb, EDIT_TEXTBOOK);

}

void StorageControl::removeTextbook(Textbook &tb){
    updateStorage(tb, REMOVE_TEXTBOOK);

}

void StorageControl::addCourse(Course &c){
    updateStorage(c, ADD_COURSE);

}

void StorageControl::editCourse(Course &c){
    updateStorage(c, EDIT_COURSE);
}

void StorageControl::removeCourse(Course &c){
    updateStorage(c, REMOVE_COURSE);

}

void StorageControl::checkout(Invoice &i){
    updateStorage(i, ADD_INVOICE);
}

void StorageControl::refreshContent(User &u, QList<Course*> &cs){
    QByteArray *req = new QByteArray();
    QByteArray *res = new QByteArray();
    serializer->serialize(u, GET_CONTENT, *req);
    connection->request(*req, *res);
    serializer->deserialize(*res, cs);
}

QByteArray* StorageControl::updateStorage(Serializable& obj, commands_t command){
    QByteArray *req = new QByteArray();
    QByteArray *res = new QByteArray();
    serializer->serialize(obj, command, *req);
    connection->request(*req, *res);
    delete req;
    return res;
}

