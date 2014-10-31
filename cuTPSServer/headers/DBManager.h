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

#include "../../common/headers/User.h"
#include "../../common/headers/Textbook.h"
#include "../../common/headers/Chapter.h"
#include "../../common/headers/Section.h"
#include "../../common/headers/Invoice.h"

using namespace std;

class DBManager {
  public:
    DBManager();
    ~DBManager();

    /* =====================================================================
      Function  : AddUsers
      Purpose   : Adds a user to the database
      Variables : In - User* - The user to add to the DB
      Returns   : - True if successful
                  - False otherwise
    ===================================================================== */
    bool AddUser(User*);

    /* =====================================================================
      Function  : RemoveUser
      Purpose   : Deletes a user from the database
      Variables : In - User* - The user to delete from the DB
      Returns   : - True if successful
                  - False otherwise
    ===================================================================== */
    bool RemoveUser(User*);

    /* =====================================================================
      Function  : ShowUsers
      Purpose   : Prints all users from the DB to the console
                  For debugging purposes only
      Variables : None
      Returns   : void
    ===================================================================== */
    void ShowUsers();

    /* =====================================================================
      Function  : StoreTextbook
      Purpose   : Stores a textbook in the DB
      Variables : In - Textbook* - The textbook to store
      Returns   : - True if successful
                  - False otherwise
    ===================================================================== */
    bool StoreTextbook (Textbook*);

    /* =====================================================================
      Function  : StoreChapter
      Purpose   : Stores a chapter in the DB
      Variables : In - Chapter* - The chapter to store
      Returns   : - True if successful
                  - False otherwise
    ===================================================================== */
    bool StoreChapter (Chapter*, QString&);

    /* =====================================================================
      Function  : StoreSection
      Purpose   : Stores a section in the DB
      Variables : In - Section* - The section to store
      Returns   : - True if successful
                  - False otherwise
    ===================================================================== */
    bool StoreSection (Section*, QString&, QString&);

    /* =====================================================================
      Function  : StoreInvoice
      Purpose   : Stores an invoice in the database
      Variables : In - Invoice* - The invoice to store
      Returns   : - True if successful
                  - False otherwise
    ===================================================================== */
    bool StoreInvoice (Invoice *);

    /* =====================================================================
      Function  : GetNewContentId
      Purpose   : Gets a new content id from the DB.
                  Note: This method assumes the DB is already open
      Variables : None
      Returns   : The new content id
    ===================================================================== */
    int GetNewContentId();

    /* =====================================================================
      Function  : RetrieveContentList
      Purpose   : Retrieves the list of content for a user
      Variables : In  - string* - The username of the student
                : Out - vector<Content>* - The list of content objects
      Returns   : True - Success
                  False - Fail
    ===================================================================== */
    void RetrieveContentList (QString &, vector<Textbook> &);
  private:
    QSqlDatabase db;
};
#endif
