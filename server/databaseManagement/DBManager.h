#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QSqlError>

#include <stdexcept>

using namespace std;

class DBManager {
    public:
        DBManager();
        ~DBManager();

        /* =====================================================================
          Function  : Login
          Purpose   : Checks whether the username/password combination is
                        correct and fills in the user's type if successful.
          Variables :
          Returns   : The user type
          Throws    : Throws runtime_error if username/password combination
                        is incorrect
        ===================================================================== */
        QString Login(QString username, QString password);

        /* =====================================================================
          Function  : AddTextbook
          Purpose   : Stores a textbook in the DB
          Variables :
          Returns   : - True if successful
                      - False otherwise
        ===================================================================== */
        void AddTextbook(QString isbn, QString title, QString publisher, QString author, int year, QString edition, QString description, bool availability, float price);

        /* =====================================================================
          Function  : GetNewContentId
          Purpose   : Gets a new content id from the DB.
                      Note: This method assumes the DB is already open
          Variables : None
          Returns   : The new content id
        ===================================================================== */
        int GetNewContentId();
    private:
        QSqlDatabase db;
};
#endif
