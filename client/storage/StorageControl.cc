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

User* StorageControl::logIn(User &u){
    u.setType("student");
    return &u;
}

void StorageControl::refreshContent(User &u, QList<Course*> &cs){
    QByteArray *req = new QByteArray();
    QByteArray *res = new QByteArray();
    serializer->serialize(u, GET_CONTENT, *req);
    connection->request(*req, *res);
    serializer->deserialize(*res, cs);
}

bool StorageControl::updateStorage(Serializable& obj, commands_t command){
    QByteArray *req = new QByteArray();
    QByteArray *res = new QByteArray();
    serializer->serialize(obj, command, *req);
    qDebug()<<*req;
    connection->request(*req, *res);
    delete req;
    return serializer->deserialize(*res);
}

