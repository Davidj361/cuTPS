#include "headers/Invoice.h"

Invoice::Invoice(QString cUsername) {
  username = cUsername;
}

vector<int>* Invoice::getContentList(){
    return contentList;
}

void Invoice::addContent(Content *c){
    contentList->push_back(c->getcid());
    return;
}

QString Invoice::getUsername() {
  return username;
}

QJsonObject* Invoice::serialize(){
    QJsonObject *json = new QJsonObject();
    (*json)["username"] = getUsername();
    QJsonArray *cidArray = new QJsonArray();
    for(vector<int>::const_iterator iter= contentList->begin(); iter != contentList->end(); ++iter){
        QJsonObject cid;
        cid["cid"] = *iter;
        cidArray->append(cid);
    }
    (*json)["contents"] = *cidArray;


    return json;
}

void Invoice::addContent(int i) { contentList->push_back(i); }
