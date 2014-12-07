#include "headers/Invoice.h"

Invoice::Invoice(const QString& cUsername) {
    username = cUsername;
}

Invoice::Invoice(const QString& cUsername, const QList<int>& content) {
    this->username = cUsername;
    this->contentList = content;
}

QList<int> &Invoice::getContentList() {
    return contentList;
}

void Invoice::addContent(Content *c) {
    if (c != 0)
        contentList.push_back(c->getcid());
}

QString Invoice::getUsername() {
    return username;
}

void Invoice::serialize(QJsonObject &inJson) {
    inJson["username"] = getUsername();
    QJsonArray cidArray;
    int i;
    foreach (i, contentList) {
        QJsonObject cid;
        cid["c_id"] = i;
        cidArray.append(cid);
    }
    inJson["contents"] = cidArray;
}

void Invoice::addContent(int i) {
    contentList.append(i);
}
