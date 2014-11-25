#ifndef USER_H
#define USER_H

#include "Definitions.h"
#include <QString>
#include <QJsonObject>


class User {

    public:

        /* =====================================================================
        Function  : Section
        Purpose   : Constructs an Section object
        Variables : IN  -  Username
                        -  Password
                        -  Type of user
                        -  Name
        Returns   : void
        ===================================================================== */
        User(QString, QString, QString, QString);

        QString getUserName();
        QString getName();
        QString getPassword();
        QString getType();
        void serialize(QJsonObject&);

    private:
        QString username;
        QString name;
        QString password;
        QString type;

};
#endif

