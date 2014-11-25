#include "headers/User.h"

User::User(QString cUsername, QString cPassword, QString cType, QString cName) {
    username = cUsername;
    password = cPassword;
    type = cType;
    name = cName;
}


QString User::getUserName() {
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

void User::serialize(QJsonObject &json){
    json.insert("username", username);
    json.insert("password", password);
    json.insert("type", type);
    json.insert("name", name);
}

