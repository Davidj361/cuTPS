#ifndef USER_H
#define USER_H

#include "Definitions.h"
#include "Serializable.h"
#include <QString>
#include <QJsonObject>


class User : public Serializable{

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
        User() {}; // This is required when you have defined other constructors;
        User(QString, QString, QString, QString);

        QString getUsername();
        QString getName();
        QString getPassword();
        QString getType();

        void setType(QString);
        void serialize(QJsonObject&);

    private:
        QString username;
        QString name;
        QString password;
        QString type;

};
#endif

