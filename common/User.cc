#include "headers/User.h"

User::User(QString cUsername, QString cName, QString cPassword,
           user_t cType) {
  username = cUsername;
  name = cName;
  password = cPassword;
  type = cType;
}

User::getName() {
  return name;
}

User::getUserName() {
  return username;
}

User::type() {
  return type;
}

