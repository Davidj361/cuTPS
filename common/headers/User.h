#ifndef USER_H
#define USER_H

#include "Definitions.h"
#include "Serializable.h"
#include <QString>
#include <QJsonObject>


class User : public Serializable {

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
        User(QString, QString);

        const QString getUsername() const;
        QString getName();
        QString getPassword();
        /* =====================================================================
        Type will be one of "student", "content_manager", "administrator"
        ===================================================================== */
        const QString& getType() const;

        void setType(QString);
        void serialize(QJsonObject&) const;

    private:
        QString username;
        QString name;
        QString password;
        QString type;

};
#endif

