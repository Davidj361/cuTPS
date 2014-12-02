#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QDebug>
#include <QString>
#include <QDateTime>

#include <stdexcept>

#include "DBManager.h"
#include "../../common/headers/User.h"
#include "../../common/headers/Textbook.h"
#include "../../common/headers/Chapter.h"
#include "../../common/headers/Section.h"
#include "../../common/headers/Invoice.h"

using namespace std;

class DBController {
    public:
        DBController();
        ~DBController();

        /* =====================================================================
          Function  : StoreTextbook
          Purpose   : Stores a textbook in the DB
          Variables : In - Textbook* - The textbook to store
          Returns   : - True if successful
                      - False otherwise
        ===================================================================== */
        void StoreTextbook (Textbook *);

        /* =====================================================================
          Function  : StoreChapter
          Purpose   : Stores a chapter in the DB
          Variables : In - Chapter* - The chapter to store
                      In - ISBN
          Returns   : - True if successful
                      - False otherwise
        ===================================================================== */
        bool StoreChapter (Chapter *, QString &);

        /* =====================================================================
          Function  : StoreSection
          Purpose   : Stores a section in the DB
          Variables : In - Section* - The section to store
                      In - ISBN
                      In - Chapter
          Returns   : - True if successful
                      - False otherwise
        ===================================================================== */
        bool StoreSection (Section *, QString &, QString &);

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
        bool RetrieveContentList (QString &, vector<Textbook *> &);

        /* =====================================================================
          Function  : Login
          Purpose   : Checks whether the username/password combination is
                        correct and fills in the user's type if successful.
          Variables : User* - The user attempting to login
          Returns   : void
          Throws    : Throws runtime_error if username/password combination
                        is incorrect
        ===================================================================== */
        void Login (User *);
    private:
        DBManager *dbManager;
};
#endif
