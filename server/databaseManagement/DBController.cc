#include "DBController.h"

using namespace std;

/***************************************************************************
 **                INITILIZE DATABASE                                     **
 **************************************************************************/
DBController::DBController() {
    dbManager = new DBManager();
}

/***************************************************************************
 **                  DESTROY DATABASE                                     **
 **************************************************************************/
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
    catch(runtime_error e) {
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
    }
    catch(runtime_error e) {
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
    }
    catch(runtime_error e) {
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
    }
    catch(runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                STORE INVOICE IN THE DATABASE                          **
 **************************************************************************/
bool DBController::AddInvoice(Invoice *invoice) {
    try {
        dbManager->AddInvoice(invoice->getUsername(), invoice->getContentList());
    }
    catch(runtime_error e) {
        throw e;
    }
}

bool DBController::RetrieveContentList (QString &username, vector<Textbook *> &list) {
//    if (!db.open())
//        throw runtime_error("ERROR DBController::RetrieveContentList() Error while performing db.open()");

//    QSqlQuery query;

//    // Get user from db
//    if (!query.exec("SELECT type FROM Users WHERE username='" + username + "'"))
//        throw runtime_error("ERROR DBController::RetrieveContentList()  Error while performing user lookup");

//    // Check if user is a student or content manager
//    if ( !query.first() || (query.value(0) != "student" && query.value(0) != "content_manager") )
//        throw runtime_error("User is not a student or does not exist");

//    if (query.value(0) == "student") {
//        // Get textbook list for courses the student is registered in
//        if (!query.prepare("SELECT Textbooks.* FROM Class_list INNER JOIN Book_List ON Class_List.course_code = Book_List.course_code INNER JOIN Textbooks ON Book_List.textbook_id = Textbooks.isbn WHERE Class_List.student = :username;"))
//            throw runtime_error("ERROR DBController::RetrieveContentList() Error while preparing join statement to get user's class list");
//        query.bindValue(":username", username);
//    }
//    else {
//        // Get all the content in the db for the content manager
//        if (!query.prepare("SELECT * FROM Textbooks"))
//            throw runtime_error("ERROR DBController::RetrieveContentList() Error while retrieving all textbooks");
//    }

//    if (!query.exec())
//        throw runtime_error("ERROR DBController::RetrieveContentList() Error while retrieving user's textbook list");

//    // Loop through each textbook, getting all the chapters and sections and creating objects
//    while (query.next()) {
//        Textbook *textbook = new Textbook(query.value(0).toString(), // ISBN
//                                          query.value(1).toString(), // Title
//                                          query.value(2).toString(), // Publisher
//                                          query.value(3).toString(), // Author
//                                          query.value(4).toInt(),    // year
//                                          query.value(5).toString(), // Edition
//                                          query.value(6).toString(), // Description
//                                          query.value(7).toBool(),   // Availability
//                                          query.value(8).toFloat(),  // Price
//                                          query.value(9).toInt());   // Content ID

//        QSqlQuery ch_query;
//        if (!ch_query.prepare("SELECT * FROM Chapters WHERE textbook = :isbn AND availability = 1;"))
//            throw runtime_error("ERROR DBController::RetrieveContentList() Error while preparing statement to look up chapter info");

//        ch_query.bindValue(":isbn", query.value(0).toString());

//        if (!ch_query.exec())
//            throw runtime_error("ERROR DBController::RetrieveContentList() Error while retrieving chapter info");

//        // Loop through each chapter, getting all the sections and creating objects
//        while (ch_query.next()) {
//            Chapter *chapter = new Chapter(ch_query.value(0).toString(),  // Name
//                                           ch_query.value(1).toInt(),     // Chapter Number
//                                           textbook,                      // Textbook
//                                           ch_query.value(3).toString(),  // Description
//                                           ch_query.value(4).toBool(),    // Availability
//                                           ch_query.value(5).toFloat(),   // Price
//                                           ch_query.value(6).toInt());    // Content ID
//            QSqlQuery sec_query;
//            if (!sec_query.prepare("SELECT * FROM Sections WHERE textbook = :isbn AND chapter = :chapter AND availability = 1;"))
//                throw runtime_error("ERROR DBController::RetrieveContentList() Error while preparing statement to look up section info");

//            sec_query.bindValue(":isbn", query.value(0));
//            sec_query.bindValue(":chapter", ch_query.value(1));

//            if (!sec_query.exec())
//                throw runtime_error("ERROR DBController::RetrieveContentList() Error while retrieving section info");

//            while (sec_query.next()) {
//                Section *section = new Section(sec_query.value(0).toString(),  // Name
//                                               sec_query.value(1).toInt(),     // Section Number
//                                               chapter,                       // Chapter
//                                               textbook,                      // Textbook
//                                               sec_query.value(4).toString(),  // Description
//                                               sec_query.value(5).toBool(),    // Availability
//                                               sec_query.value(6).toFloat(),   // Price
//                                               sec_query.value(7).toInt());    // Content ID

//                chapter->addSection(section);
//                // qDebug() << "Section: " << section.getTitle() << " added to chapter " << chapter.getTitle() << " of book " << textbook.getTitle();
//            }
//            textbook->addChapter(chapter);
//            // qDebug() << "Chapter: " << chapter.getTitle() << " added to book " << textbook.getTitle();
//        }
//        // qDebug() << "Textbook "  << textbook.getTitle() << " added to vector list";
//        list.push_back(textbook);
//    }
    return true;
}

/***************************************************************************
 **                DISPLAYS THE NAMES OF TABLES IN DATABASE               **
 **************************************************************************/
/*void displayTables(QSqlDatabase* db) {
    for (int i=0; i < db->tables().size(); i++)
        qDebug() << db->tables().at(i);
    qDebug() << endl;
}*/

/***************************************************************************
 **                DISPLAY FIELDS IN A TABLE                              **
 **************************************************************************/
//void DBController::viewFields(QString table) {
//    if (db.open()) {
//        QSqlRecord rec = db.record(table);
//        for (int i = 0; i < rec.count(); i++) {
//            qDebug() << rec.fieldName(i);
//        }
//    }

//}

/***************************************************************************
 **                ADD NEW COURSE                                         **
 **************************************************************************/
/*void addCourse(QSqlDatabase* db, QString code, QString name) {
    if (db->open()) {
        QSqlQuery query;
        query.exec("SELECT * FROM Courses WHERE code = '"+code+"'");
        if (query.first())
            qDebug() << code << "already exists in Courses";
        else {
            query.prepare("INSERT INTO Courses VALUES (:code,:name)");
            query.bindValue(":code", code);
            query.bindValue(":name", name);
            query.exec();
            qDebug() << code << "was added in Courses";
        }
    }
}*/

/***************************************************************************
 **                REMOVE COURSE FROM COURSES                             **
 **************************************************************************/
/*bool removeCourse(QSqlDatabase* db, QString code) {
    if (db->open()) {
        QSqlQuery query;
        query.exec("SELECT * FROM Courses WHERE code = '"+code+"'");
        if (query.first()) {
            query.exec("DELETE FROM Courses WHERE code = '"+code+"'");
            qDebug() << code << "was removed";
            return true;
        } else {
            qDebug() << code << "does not exist and cannot be removed";
            return false;
        }

    }
    return false;
}*/

/***************************************************************************
 **                DISPLAY RECORDS IN A TABLE                             **
 **************************************************************************/
/*void displayRecordsInTable(QSqlDatabase* db, QString table) {
    if (db->open()) {
        QSqlQuery query;
        query.exec("SELECT * FROM "+table);
        while (query.next()){
            qDebug() << query.value(0).toString();
        }
    }
}*/

/***************************************************************************
 **                DELETE ALL RECORDS IN A TABLE                          **
 **************************************************************************/
/*void deleteRecordsInTable(QSqlDatabase* db, QString table) {
    if (db->open()) {
        QSqlQuery query;
        query.exec("DELETE FROM "+table);
    }
}*/

/***************************************************************************
 **                REMOVE RECORD IN CONTENT                               **
 **************************************************************************/
/*void removeContentId(QSqlDatabase* db, QString id) {
    if (db->open()) {
        QSqlQuery query;
        query.exec("SELECT * FROM Content WHERE id = "+id);
        if (query.first()) {
            query.exec("DELETE FROM Content WHERE id = "+id);
            qDebug() << "A Content was remove";
        }
    }
} */

/***************************************************************************
 **                NEW RECORD IN TEXTBOOKS                                **
 **************************************************************************/
/*  textBookDetails Indexing
 *  0 = isbn
 *  1 = title
 *  2 = publisher
 *  3 = author
 *  4 = edition
 *  5 = description
 *
 */
/*void addNewTextbook(QSqlDatabase* db, QStringList textbookDetails, int year, int availability, double price) {
    if (db->open()) {
        QSqlQuery query;
        query.exec("SELECT * FROM Textbooks WHERE isbn = '"+textbookDetails.at(0)+"'");
        if (query.first()) {
            qDebug() << textbookDetails.at(1) << " is already in the database";
        } else {
            int content_id = addNewContentId(db, "textbook");
            query.prepare("INSERT INTO Textbooks VALUES (:isbn,:title,:publisher,:author,:year,:edition,:description,:availability,:price, :content_id)");
            query.bindValue(":isbn", textbookDetails.at(0));
            query.bindValue(":title", textbookDetails.at(1));
            query.bindValue(":publisher", textbookDetails.at(2));
            query.bindValue(":author", textbookDetails.at(3));
            query.bindValue(":year", year);
            query.bindValue(":edition", textbookDetails.at(4));
            query.bindValue(":description", textbookDetails.at(5));
            query.bindValue(":availability", availability);
            query.bindValue(":price", price);
            query.bindValue(":content_id",content_id);
            query.exec();
            qDebug() << textbookDetails.at(1) << "was added to Textbooks database";
        }
    }
} */

/***************************************************************************
 **                MODIFY RECORD IN TEXTBOOKS                             **
 **************************************************************************/
/*  textBookDetails Indexing
 *  0 = isbn
 *  1 = title
 *  2 = publisher
 *  3 = author
 *  4 = edition
 *  5 = description
 *
 */
/*void modifyTextbook(QSqlDatabase* db, QStringList textbookDetails, int year, int availability, double price, int content_id) {
    if (db->open()) {
        qDebug() << content_id;
        QSqlQuery query;
        query.exec("SELECT * FROM Textbooks WHERE content_id = 1");
        if (query.first()) {
            qDebug() << textbookDetails.at(1) << " is about to be modified";
            query.exec("UPDATE Textbooks SET isbn = '"+textbookDetails.at(0)+"', title = '"+textbookDetails.at(1)+"', publisher = '"+textbookDetails.at(2)+"', author = '"+textbookDetails.at(3)+"', edition = '"+textbookDetails.at(4)+"', description = '"+textbookDetails.at(5)+"', year = "+year+", availability = "+availability+", price = "+price+" WHERE content_id = "+content_id);
            qDebug() << textbookDetails.at(1) << "was successfully modified";
        } else {
            qDebug() << "Couldn't find the textbook";
        }
    }
}*/



/***************************************************************************
 **                DELETE RECORD IN TEXTBOOKS                             **
 **************************************************************************/
/*bool deleteTextbook(QSqlDatabase* db, QString isbn) {
    if (db->open()) {
        QSqlQuery query;
        query.exec("SELECT * FROM Textbooks WHERE isbn = "+isbn);
        if (query.first()) {
            query.exec("DELETE FROM Textbooks WHERE isbn = "+isbn);
            qDebug() << isbn << " was remove";
            return true;
        }
    }
    return false;
}*/
