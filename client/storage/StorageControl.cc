#include "StorageControl.h"


StorageControl::StorageControl( QString inIp ) {

    // TODO figure out how to retrieve ip
    ip = inIp;
    connection = new ConnectionClient(&ip);
    serializer = new ClientSerializer();

}

void StorageControl::setIP( QString inIP ) {

    ip = inIP;
    delete connection;
    connection = new ConnectionClient(&ip);

}

StorageControl::~StorageControl(){

    delete connection;
    delete serializer;

}

void StorageControl::addTextbook( Class &clss ) const{

    updateStorage(clss, ADD_TEXTBOOK);

}

void StorageControl::editTextbook( Textbook &tb ) const{

    updateStorage(tb, EDIT_TEXTBOOK);

}

void StorageControl::removeTextbook( Textbook &tb ) const{

    updateStorage(tb, REMOVE_TEXTBOOK);

}

void StorageControl::addChapter( Chapter &ch ) const{

    updateStorage(ch, ADD_CHAPTER);

}

void StorageControl::editChapter( Chapter &ch ) const{

    updateStorage(ch, EDIT_CHAPTER);

}

void StorageControl::removeChapter( Chapter &ch ) const{

    updateStorage(ch, REMOVE_CHAPTER);

}

void StorageControl::addSection( Section &s ) const{

    updateStorage(s, ADD_SECTION);

}

void StorageControl::editSection( Section & s) const{

    updateStorage(s, EDIT_SECTION);

}

void StorageControl::removeSection( Section &s ) const{

    updateStorage(s, REMOVE_SECTION);

}

void StorageControl::addClass( Class &c ) const {

    updateStorage(c, ADD_CLASS);

}

void StorageControl::editClass( Class &c ) const{

    updateStorage(c, EDIT_CLASS);

}

void StorageControl::removeClass( Class &c ) const{

    updateStorage(c, DELETE_CLASS);

}

void StorageControl::removeCourse( Course &course ) const {

    updateStorage(course, REMOVE_COURSE);

}

void StorageControl::checkout( Invoice &i ) const {

    try{
        updateStorage(i, ADD_INVOICE);
    } catch (std::runtime_error e){
        throw e;
    }

}

void StorageControl::logIn( User &u ) const {

    QByteArray *req = new QByteArray();
    QByteArray *res = new QByteArray();
    serializer->serialize(u, LOGIN, *req);
    connection->request(*req, *res);
    try {
        serializer->deserialize(*res, u);
    } catch (std::runtime_error e) {
        delete req;
        delete res;
        throw e;
    }
    delete req;
    delete res;

}

void StorageControl::refreshContent( User &u, QList<Class*> &cs ) const {

    QByteArray *req = new QByteArray();
    QByteArray *res = new QByteArray();
    serializer->serialize(u, GET_CONTENT, *req);
    connection->request(*req, *res);

    try {
        serializer->deserialize(*res, cs);
    } catch (std::runtime_error e) {
        delete req;
        delete res;
        throw e;
    }
    delete req;
    delete res;

}

void StorageControl::updateStorage( Serializable& obj, commands_t command ) const {

    QByteArray *req = new QByteArray();
    QByteArray *res = new QByteArray();
    serializer->serialize(obj, command, *req);
    connection->request(*req, *res);

    try {
        serializer->deserialize(*res);
    } catch (std::runtime_error e) {
        delete req;
        delete res;
        throw e;
    }
    delete req;
    delete res;

}

