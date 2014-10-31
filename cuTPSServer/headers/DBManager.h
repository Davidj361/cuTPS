#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QString>

#include <stdexcept>

#include "../common/headers/User.h"
#include "../common/headers/Textbook.h"
#include "../common/headers/Chapter.h"

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
      Returns   : void
    ===================================================================== */
    bool StoreTextbook (Textbook*);

    /* =====================================================================
      Function  : StoreTextbook
      Purpose   : Stores a textbook in the DB
      Variables : In - Textbook* - The textbook to store
      Returns   : void
    ===================================================================== */
    bool StoreChapter (Chapter*, QString);

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
      Returns   : 1 - Success
                  0 - Fail
      TODO: Change string to Content when the class has been created
    ===================================================================== */
    //int RetrieveContentList (string *, vector<string> *);

    /* =====================================================================
    Function  : StoreContent
    Purpose   : Stores content in the database
    Variables : In  - Content* - The object to store
    Returns   : 1 - Success
                0 - Fail
    TODO: Change string to Content when the class has been created
    ===================================================================== */
   // int StoreContent (string *);

    /* =====================================================================
      Function  : StoreInvoice
      Purpose   : Stores an invoice in the database
      Variables : In - Invoice* - The invoice to store
      Returns   : 1 - Success
                  0 - Fail
      TODO: Change string to Invoice when the class has been created
    ===================================================================== */
   // int StoreInvoice (string *);
  private:
    QSqlDatabase db;
};
#endif
