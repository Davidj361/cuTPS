#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QSqlError>
#include <QList>

#include "../../common/headers/Textbook.h"
#include "../../common/headers/Class.h"
#include "../../common/headers/Course.h"

#include <stdexcept>

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
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void AddTextbook(QString isbn, QString title, QString publisher, QString author, int year, QString edition, QString description, bool availability, float price);

        /* =====================================================================
          Function  : EditTextbook
          Purpose   : Edits a textbook in the DB
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void EditTextbook(QString isbn, QString title, QString publisher, QString author, int year, QString edition, QString description, bool availability, float price, int content_id);

        /* =====================================================================
          Function  : DeleteTextbook
          Purpose   : Deletes a Textbook from the DB
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void DeleteTextbook(Textbook *textbook);

        /* =====================================================================
          Function  : AddChapter
          Purpose   : Stores a chapter in the DB
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void AddChapter(QString title, int number, QString textbook, QString description, bool available, float price);

        /* =====================================================================
          Function  : EditChapter
          Purpose   : Edits a chapter in the DB
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void EditChapter(QString title, int number, QString textbook, QString description, bool available, float price, int content_id);

        /* =====================================================================
          Function  : DeleteChapter
          Purpose   : Deletes a Chapter from the DB
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void DeleteChapter(Chapter *chapter);

        /* =====================================================================
          Function  : AddSection
          Purpose   : Stores a section in the DB
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void AddSection(QString title, int number, int chapter, QString textbook, QString description, bool available, float price);

        /* =====================================================================
          Function  : EditSection
          Purpose   : Edits a section in the DB
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void EditSection(QString title, int number, int chapter, QString textbook, QString description, bool available, float price, int content_id);

        /* =====================================================================
          Function  : DeleteSection
          Purpose   : Deletes a Section from the DB
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void DeleteSection(Section *section);

        /* =====================================================================
          Function  : AddCourse
          Purpose   : Stores a Course in the DB
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void AddCourse(QString coursecode, QString coursetitle);

        /* =====================================================================
          Function  : EditCourse
          Purpose   : Edits a Course in the DB
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void EditCourse(QString coursecode, QString coursetitle, QString newcoursecode);

        /* =====================================================================
          Function  : DeleteCourse
          Purpose   : Deletes a course from the DB
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void DeleteCourse(QString coursecode);

        /* =====================================================================
          Function  : AddClass
          Purpose   : Stores a Class in the DB
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void AddClass(QString classcode, QString classtitle);

        /* =====================================================================
          Function  : DeleteClass
          Purpose   : Deletes a Class from the DB
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void DeleteClass(QString classcode, QString semester);

        /* =====================================================================
          Function  : AddTextbooksToClass
          Purpose   : Adds a list of Textbooks to a Class
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void AddTextbooksToClass (QList<Textbook *> &list, QString course, QString semester);

        /* =====================================================================
          Function  : RemoveTextbooksFromClass
          Purpose   : Removes a list of Textbooks from a Class
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void RemoveTextbooksFromClass (QList<Textbook *> &list, QString course, QString semester);

        /* =====================================================================
          Function  : AddInvoice
          Purpose   : Stores an invoice in the DB
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void AddInvoice(QString username, QList<int> cart);

        /* =====================================================================
          Function  : RetrieveContentList
          Purpose   : Retrieves the list of content for a user
          Variables :
          Returns   : void
          Throws    : Throws runtime_error if there is any error
        ===================================================================== */
        void RetrieveContentList(QString username, QList<Class *> &list);

        /* =====================================================================
          Function  : GetNewContentId
          Purpose   : Gets a new content id from the DB.
                      Note: This method assumes the DB is already open
          Variables : None
          Returns   : The new content id
        ===================================================================== */
        int GetNewContentId(QString type);

        /* =====================================================================
          Function  : CourseExists
          Purpose   : Checks whether the course exists already
          Variables : In  - QString* - The course code
          Returns   : True - The course exists
                      False - The course doesn't exist
        ===================================================================== */
        bool CourseExists(QString);
    private:

        void GetClassesForStudent(QList<Class *> &list, QString username);
        void GetAllClasses(QList<Class *> &list);
        void GetTextbooksForClass(QList<Textbook *> &list, QString course, QString semester);
        void GetChaptersForTextbook(Textbook *textbook);
        void GetSectionsForChapter(Textbook *textbook, Chapter *chapter);

        QSqlDatabase db;
};
#endif
