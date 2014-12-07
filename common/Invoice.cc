#include "headers/Invoice.h"

Invoice::Invoice(const QString& cUsername) {
    username = cUsername;
}

Invoice::Invoice(const QString& cUsername, const QList<int>& content) {
    this->username = cUsername;
    this->contentList = content;
}

const QList<int> &Invoice::getContentList() const {
    return contentList;
}

void Invoice::addContent(Content *c) {
    if (c != 0)
        contentList.push_back(c->getcid());
}

QString Invoice::getUsername() const {
    return username;
}

void Invoice::serialize(QJsonObject &inJson) const {
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
