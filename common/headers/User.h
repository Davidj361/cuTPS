#ifndef USER_H
#define USER_H

#include "Definitions.h"
#include <QString>


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

  private:
    QString username;
    QString name;
    QString password;
    QString type;

};
#endif

