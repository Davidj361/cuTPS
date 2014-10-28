#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <string>
#include <vector>

using namespace std;

class DBManager {
public:
  DBManager();
  ~DBManager();

  /* =====================================================================
    Function  : RetrieveContentList
    Purpose   : Retrieves the list of content for a user
    Variables : In  - string* - The username of the student
              : Out - vector<Content>* - The list of content objects
    Returns   : 1 - Success
                0 - Fail
    TODO: Change string to Content when the class has been created
  ===================================================================== */
  int RetrieveContentList (string*, vector<string>*);

    /* =====================================================================
    Function  : StoreContent
    Purpose   : Stores content in the database
    Variables : In  - Content* - The object to store
    Returns   : 1 - Success
                0 - Fail
    TODO: Change string to Content when the class has been created
  ===================================================================== */
  int StoreContent (string*);

  /* =====================================================================
    Function  : StoreInvoice
    Purpose   : Stores an invoice in the database
    Variables : In - Invoice* - The invoice to store
    Returns   : 1 - Success
                0 - Fail
    TODO: Change string to Invoice when the class has been created
  ===================================================================== */
  int StoreInvoice (string*);
private:
};
#endif
