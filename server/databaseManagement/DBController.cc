#include "DBController.h"

using namespace std;

DBController::DBController() {
    dbManager = new DBManager();
}

DBController::~DBController() {
    delete dbManager;
}

/***************************************************************************
 **                LOGIN                                                  **
 **************************************************************************/
void DBController::Login(User *user) {
    try {
        user->setType(dbManager->Login(user->getUsername(), user->getPassword()));
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                STORE TEXTBOOK IN THE DATABASE                         **
 **************************************************************************/
void DBController::AddTextbook(Textbook *textbook) {
    try {
        dbManager->AddTextbook(textbook->getISBN(),
                              textbook->getTitle(),
                              textbook->getPublisher(),
                              textbook->getAuthor(),
                              textbook->getYear(),
                              textbook->getEdition(),
                              textbook->getDescription(),
                              textbook->isAvailable(),
                              textbook->getPrice());
        if (DEBUG) qDebug() << "DBController - Added Textbook - " << textbook->getTitle();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                EDIT TEXTBOOK IN THE DATABASE                          **
 **************************************************************************/
void DBController::EditTextbook(Textbook *textbook) {
    try {
        dbManager->EditTextbook(textbook->getISBN(),
                              textbook->getTitle(),
                              textbook->getPublisher(),
                              textbook->getAuthor(),
                              textbook->getYear(),
                              textbook->getEdition(),
                              textbook->getDescription(),
                              textbook->isAvailable(),
                              textbook->getPrice(),
                              textbook->getcid());
        if (DEBUG) qDebug() << "DBController - Edited Textbook - " << textbook->getTitle();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                DELETE TEXTBOOK FROM THE DATABASE                      **
 **************************************************************************/
void DBController::DeleteTextbook(Textbook *textbook) {
    try {
        dbManager->DeleteTextbook(textbook);
        if (DEBUG) qDebug() << "DBController - Deleted Textbook - " << textbook->getTitle();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                STORE CHAPTER IN THE DATABASE                          **
 **************************************************************************/
void DBController::AddChapter(Chapter *chapter) {
    try {
        dbManager->AddChapter(chapter->getTitle(),
                              chapter->getChapterNo(),
                              chapter->getTextbook()->getISBN(),
                              chapter->getDescription(),
                              chapter->isAvailable(),
                              chapter->getPrice());
        if (DEBUG) qDebug() << "DBController - Added Chapter - " <<  chapter->getChapterNo() << " - " << chapter->getTitle();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                EDIT CHAPTER IN THE DATABASE                           **
 **************************************************************************/
void DBController::EditChapter(Chapter *chapter) {
    try {
        dbManager->EditChapter(chapter->getTitle(),
                              chapter->getChapterNo(),
                              chapter->getTextbook()->getISBN(),
                              chapter->getDescription(),
                              chapter->isAvailable(),
                              chapter->getPrice(),
                              chapter->getcid());
        if (DEBUG) qDebug() << "DBController - Edited Chapter - " << chapter->getChapterNo() << " - " << chapter->getTitle();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                DELETE CHAPTER FROM THE DATABASE                       **
 **************************************************************************/
void DBController::DeleteChapter(Chapter *chapter) {
    try {
        dbManager->DeleteChapter(chapter);
        if (DEBUG) qDebug() << "DBController - Deleted Chapter - " << chapter->getChapterNo() << " - " << chapter->getTitle();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                STORE SECTION IN THE DATABASE                          **
 **************************************************************************/
void DBController::AddSection(Section *section) {
    try {
        dbManager->AddSection(section->getTitle(),
                             section->getSectionNo(),
                             section->getChapter()->getChapterNo(),
                             section->getTextbook()->getISBN(),
                             section->getDescription(),
                             section->isAvailable(),
                             section->getPrice());
        if (DEBUG) qDebug() << "DBController - Added Section - " << section->getSectionNo() << " - " << section->getTitle();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                EDIT SECTION IN THE DATABASE                           **
 **************************************************************************/
void DBController::EditSection(Section *section) {
    try {
        dbManager->EditSection(section->getTitle(),
                             section->getSectionNo(),
                             section->getChapter()->getChapterNo(),
                             section->getTextbook()->getISBN(),
                             section->getDescription(),
                             section->isAvailable(),
                             section->getPrice(),
                             section->getcid());
        if (DEBUG) qDebug() << "DBController - Edited Section - " << section->getSectionNo() << " - " << section->getTitle();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                DELETE SECTION FROM THE DATABASE                       **
 **************************************************************************/
void DBController::DeleteSection(Section *section) {
    try {
        dbManager->DeleteSection(section);
        if (DEBUG) qDebug() << "DBController - Deleted Section - " << section->getSectionNo() << " - " << section->getTitle();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                STORE COURSE IN THE DATABASE                           **
 **************************************************************************/
void DBController::AddCourse(Course *course) {
    try {
        dbManager->AddCourse(course->getCourseCode(),
                             course->getCourseTitle());
        if (DEBUG) qDebug() << "DBController - Added Course - " << course->getCourseCode() << " - " << course->getCourseTitle();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                EDIT COURSE IN THE DATABASE                            **
 **************************************************************************/
void DBController::EditCourse(Course *course) {
    try {
        dbManager->EditCourse(course->getCourseCode(),
                              course->getCourseTitle(),
                              course->getNewCourseCode());
        if (DEBUG) qDebug() << "DBController - Edited Course - " << course->getCourseCode() << " - " << course->getCourseTitle();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                DELETE COURSE FROM THE DATABASE                        **
 **************************************************************************/
void DBController::DeleteCourse(Course *course) {
    try {
        dbManager->DeleteCourse(course->getCourseCode());
        if (DEBUG) qDebug() << "DBController - Deleted Course - " << course->getCourseCode() << " - " << course->getCourseTitle();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                STORE CLASS IN THE DATABASE                           **
 **************************************************************************/
void DBController::AddClass(Class *clss) {
    try {
        dbManager->AddClass(clss->getCourse()->getCourseCode(),
                            clss->getSemester());
        if (DEBUG) qDebug() << "DBController - Added Class - " << clss->getSemester() << " - " << clss->getCourse()->getCourseCode();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

//
// There's no edit class because the table consists of only 2 foreign keys.
// There is no easy way to update this as each column is required to identify
// the class.  If a user wants to 'edit' a class they must delete it and
// create a new class.
//

/***************************************************************************
 **                DELETE CLASS FROM THE DATABASE                         **
 **************************************************************************/
void DBController::DeleteClass(Class *clss) {
    try {
        dbManager->DeleteClass(clss->getCourse()->getCourseCode(), clss->getSemester());
        if (DEBUG) qDebug() << "DBController - Deleted Class - " << clss->getSemester() << " - " << clss->getCourse()->getCourseCode();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                ADD TEXTBOOKS TO CLASS                                 **
 **************************************************************************/
void DBController::AddTextbooksToClass (Class *clss) {
    try {
        dbManager->AddTextbooksToClass(clss->getBooklist(), clss->getCourse()->getCourseCode(), clss->getSemester());
        if (DEBUG) qDebug() << "DBController - Added Textbook " << clss->getBooklist()[0]->getISBN() << " to class " << clss->getSemester() << " " << clss->getCourse()->getCourseCode();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                REMOVE TEXTBOOKS FROM CLASS                            **
 **************************************************************************/
void DBController::RemoveTextbooksFromClass (Class *clss) {
    try {
        dbManager->RemoveTextbooksFromClass(clss->getBooklist(), clss->getCourse()->getCourseCode(), clss->getSemester());
        if (DEBUG) qDebug() << "DBController - Removed Textbook " << clss->getBooklist()[0]->getISBN() << " from class " << clss->getSemester() << " " << clss->getCourse()->getCourseCode();
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                STORE INVOICE IN THE DATABASE                          **
 **************************************************************************/
void DBController::AddInvoice(Invoice *invoice) {
    try {
        dbManager->AddInvoice(invoice->getUsername(), invoice->getContentList());
        if (DEBUG) qDebug() << "DBController - Added Invoice - " << invoice->getUsername() << " - " << invoice->getContentList().size() << " items";
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
**                RETRIEVE CONTENT FROM THE DATABASE                      **
***************************************************************************/
void DBController::RetrieveContentList (QString &username, QList<Class *> &list) {
    try {
        dbManager->RetrieveContentList(username, list);
        if (DEBUG) qDebug() << "DBController - Retrieved textbooks for " << username;
        // TODO - Delete this for loop
//        foreach (Class *clss, list) {
//            qDebug() << clss->getCourse()->getCourseCode() << " - " << clss->getCourse()->getCourseTitle() << " - " << clss->getSemester();
//        }
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

/***************************************************************************
**                CHECK IF COURSE EXISTS IN DATABASE                     **
***************************************************************************/
bool DBController::CourseExists(Course *course) {
    try {
        return dbManager->CourseExists(course->getCourseCode());
    }
    catch(std::runtime_error e) {
        throw e;
    }
}
