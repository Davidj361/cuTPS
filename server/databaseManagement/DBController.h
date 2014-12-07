#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QDebug>
#include <QString>
#include <QDateTime>

#include <stdexcept>

#include "DBManager.h"
#include "../../common/headers/User.h"
#include "../../common/headers/Course.h"
#include "../../common/headers/Textbook.h"
#include "../../common/headers/Chapter.h"
#include "../../common/headers/Section.h"
#include "../../common/headers/Invoice.h"

class DBController {
    public:
        DBController();
        ~DBController();

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

        /* =====================================================================
          Function  : AddTextbook
          Purpose   : Stores a textbook in the DB
          Variables : In - Textbook* - The textbook to store
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void AddTextbook (Textbook *);

        /* =====================================================================
          Function  : EditTextbook
          Purpose   : Edits a textbook in the DB
          Variables : In - Textbook* - The textbook to edit
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void EditTextbook (Textbook *);

        /* =====================================================================
          Function  : DeleteTextbook
          Purpose   : Deletes a textbook from the DB
          Variables : In - Textbook* - The textbook to delete
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void DeleteTextbook (Textbook *);

        /* =====================================================================
          Function  : AddChapter
          Purpose   : Stores a chapter in the DB
          Variables : In - Chapter* - The chapter to store
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void AddChapter(Chapter *);

        /* =====================================================================
          Function  : EditChapter
          Purpose   : Edits a chapter in the DB
          Variables : In - Chapter* - The chapter to edit
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void EditChapter(Chapter *);

        /* =====================================================================
          Function  : DeleteChapter
          Purpose   : Deletes a chapter from the DB
          Variables : In - Chapter* - The chapter to delete
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void DeleteChapter(Chapter *);


        /* =====================================================================
          Function  : AddSection
          Purpose   : Stores a section in the DB
          Variables : In - Section* - The section to store
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void AddSection (Section *);

        /* =====================================================================
          Function  : EditSection
          Purpose   : Edits a section in the DB
          Variables : In - Section* - The section to edit
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void EditSection (Section *);

        /* =====================================================================
          Function  : DeleteSection
          Purpose   : Deletes a section from the DB
          Variables : In - Section* - The section to delete
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void DeleteSection (Section *);

        /* =====================================================================
          Function  : AddCourse
          Purpose   : Stores a Course in the DB
          Variables : In - Course* - The Course to store
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void AddCourse (Course *);

        /* =====================================================================
          Function  : EditCourse
          Purpose   : Edits a Course in the DB
          Variables : In - Course* - The Course to edit
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void EditCourse (Course *);

        /* =====================================================================
          Function  : DeleteCourse
          Purpose   : Deletes a Course from the DB
          Variables : In - Course* - The Course to delete
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void DeleteCourse (Course *);

        /* =====================================================================
          Function  : AddClass
          Purpose   : Stores a Class in the DB
          Variables : In - Class* - The Class to store
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void AddClass (Class *);

        /* =====================================================================
          Function  : DeleteClass
          Purpose   : Deletes a Class from the DB
          Variables : In - Class* - The Class to delete
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void DeleteClass (Class *);

        /* =====================================================================
          Function  : AddStudentsToClass
          Purpose   : Adds a list of Students to a Class
          Variables : In - Class* - The Class being added to containing
                      the list of Students to add to it.
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void AddStudentsToClass (Class *);

        /* =====================================================================
          Function  : RemoveStudentsFromClass
          Purpose   : Removes a list of Students from a Class
          Variables : In - Class* - The Class being removed from containing
                      the list of Students to remove from it.
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void RemoveStudentsFromClass (Class *);

        /* =====================================================================
          Function  : AddTextbooksToClass
          Purpose   : Adds a list of Textbooks to a Class
          Variables : In - Class* - The Class being added to containing
                      the list of Textbooks to add to it.
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void AddTextbooksToClass (Class *);

        /* =====================================================================
          Function  : RemoveTextbooksFromClass
          Purpose   : Removes a list of Textbooks from a Class
          Variables : In - Class* - The Class being removed from containing
                      the list of Textbooks to remove from it.
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void RemoveTextbooksFromClass (Class *);

        /* =====================================================================
          Function  : StoreInvoice
          Purpose   : Stores an invoice in the database
          Variables : In - Invoice* - The invoice to store
          Returns   : - True if successful
                      - False otherwise
        ===================================================================== */
        void AddInvoice (Invoice *);

        /* =====================================================================
          Function  : RetrieveContentList
          Purpose   : Retrieves the list of content for a user
          Variables : In  - string* - The username of the student
                    : Out - QList<Class *>& - The list of class objects
          Returns   : void
        ===================================================================== */
        void RetrieveContentList (QString &, QList<Class *> &);

        /* =====================================================================
          Function  : CourseExists
          Purpose   : Checks whether the course exists already
          Variables : In  - Course* - The course
          Returns   : True - The course exists
                      False - The course doesn't exist
        ===================================================================== */
        bool CourseExists(Course *);
    private:
        DBManager *dbManager;
        const static bool DEBUG = true;
};
#endif
