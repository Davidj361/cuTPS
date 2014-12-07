#include "headers/User.h"

User::User(QString cUsername, QString cPassword, QString cType, QString cName) {
    username = cUsername;
    password = cPassword;
    type = cType;
    name = cName;
}

User::User(QString cUsername, QString cPassword){
    username = cUsername;
    password = cPassword;
    type = "";
    name = "";
}

const QString User::getUsername() const {
    return username;
}

QString User::getPassword() {
    return password;
}

QString User::getType() {
    return type;
}

QString User::getName() {
    return name;
}

void User::setType(QString type) {
    this->type = type;
}

void User::serialize(QJsonObject &json) const {
    json.insert("username", username);
    json.insert("password", password);
    json.insert("type", type);
    json.insert("name", name);
}

