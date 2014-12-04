#include "StorageControl.h"


StorageControl::StorageControl(){
    // TODO figure out how to retrieve ip
    ip = "127.0.0.1";
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

void StorageControl::addChapter(Chapter &ch){
    updateStorage(ch, ADD_CHAPTER);
}

void StorageControl::editChapter(Chapter &ch){
    updateStorage(ch, EDIT_CHAPTER);
}

void StorageControl::removeChapter(Chapter &ch){
    updateStorage(ch, REMOVE_CHAPTER);
}

void StorageControl::addSection(Section &s){
    updateStorage(s, ADD_SECTION);
}

void StorageControl::editSection(Section &s){
    updateStorage(s, EDIT_SECTION);
}

void StorageControl::removeSection(Section &s){
    updateStorage(s, REMOVE_SECTION);
}

void StorageControl::addClass(Class &c){
    updateStorage(c, ADD_CLASS);
}

void StorageControl::editClass(Class &c){
    updateStorage(c, EDIT_CLASS);
}

void StorageControl::removeClass(Class   &c){
    updateStorage(c, DELETE_CLASS);
}

void StorageControl::checkout(Invoice &i) const {
    updateStorage(i, ADD_INVOICE);
}

void StorageControl::logIn(User &u){
    QByteArray *req = new QByteArray();
    QByteArray *res = new QByteArray();
    serializer->serialize(u, LOGIN, *req);
    connection->request(*req, *res);
    try {
        serializer->deserialize(*res, u);
    }
    catch (runtime_error e) {
        throw e;
    }
}

void StorageControl::refreshContent(User &u, QList<Class*> &cs){
    QByteArray *req = new QByteArray();
    QByteArray *res = new QByteArray();
    serializer->serialize(u, GET_CONTENT, *req);
    connection->request(*req, *res);
    serializer->deserialize(*res, cs);
}

bool StorageControl::updateStorage(Serializable& obj, commands_t command) const {
    QByteArray *req = new QByteArray();
    QByteArray *res = new QByteArray();
    serializer->serialize(obj, command, *req);
    qDebug()<<*req;
    connection->request(*req, *res);
    delete req;

    return serializer->deserialize(*res);
}

