#include "headers/Invoice.h"

Invoice::Invoice(QString cUsername) {
    username = cUsername;
    contentList = new vector<int>();
}

Invoice::~Invoice() {
    if (contentList != 0) {
        delete contentList;
        contentList = 0;
    }
}

vector<int> *Invoice::getContentList() {
    return contentList;
}

void Invoice::addContent(Content *c) {
    if (c != 0)
        contentList->push_back(c->getcid());
}

QString Invoice::getUsername() {
    return username;
}

void Invoice::serialize(QJsonObject &inJson) {
    inJson["username"] = getUsername();
    QJsonArray cidArray;
    for (vector<int>::const_iterator iter = contentList->begin(); iter != contentList->end(); ++iter) {
        QJsonObject cid;
        cid["cid"] = *iter;
        cidArray.append(cid);
    }
    inJson["contents"] = cidArray;
}

void Invoice::addContent(int i) {
    contentList->push_back(i);
}
