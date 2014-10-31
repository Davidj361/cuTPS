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

void Invoice::serialize(QJsonObject& inJson){
    inJson["username"] = getUsername();
    QJsonArray cidArray;
    for(vector<int>::const_iterator iter= contentList->begin(); iter != contentList->end(); ++iter){
        QJsonObject cid;
        cid["cid"] = *iter;
        cidArray.append(cid);
    }
    inJson["contents"] = cidArray;

}
