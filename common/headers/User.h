#ifndef USER_H
#define USER_H

#include "Definitions.h"

class User {
    public:
        User(QString, QString, QString, user_t);
        QString getUserName();
        QString getName();
        user_t  getType();
    private:
        QString username;
        QString name;
        QString password;
        user_t type;


};
#endif

