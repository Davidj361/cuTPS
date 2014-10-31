#include "headers/DBManager.h"

using namespace std;

/***************************************************************************
 **                INITILIZE DATABASE                                     **
 **************************************************************************/
DBManager::DBManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./../resources/cuTPS.db"); // Connect to the database
}

/***************************************************************************
 **                  DESTROY DATABASE                                     **
 **************************************************************************/
DBManager::~DBManager() {

}

/***************************************************************************
 **                ADD A USER TO DATABASE                                 **
 **************************************************************************/
bool DBManager::AddUser(User* user) {
    bool result = false;

    if (!db.open())
        throw runtime_error("ERROR DBManager::AddUser() Error while performing db.open()");

    QSqlQuery query;

    QString username = user->getUserName();
    QString password = user->getPassword();
    QString type = user->getType();
    QString name = user->getName();

    if (!query.exec("SELECT * FROM Users WHERE username = '" + username + "'"))
        throw runtime_error("ERROR DBManager::AddUser() Error while searching for user");

    if (query.first()) {
        result = false;
    } else {
        if (!query.prepare("INSERT INTO Users VALUES (:username,:password,:type,:name)"))
            throw runtime_error("ERROR DBManager::AddUser() Error while preparing INSERT statement");

        query.bindValue(":username", username);
        query.bindValue(":password", password);
        query.bindValue(":type", type);
        query.bindValue(":name", name);

        if (query.exec())
            result = true;
        else
            throw runtime_error("ERROR DBManager::AddUser() Error while inserting user");
    }
    db.close();

    return result;
}

/***************************************************************************
 **                REMOVE A USER TO DATABASE                              **
 **************************************************************************/
bool DBManager::RemoveUser(User* user) {
    bool result = false;

    if (!db.open())
        throw runtime_error("ERROR DBManager::RemoveUser() Error while performing db.open()");

    QSqlQuery query;

    QString username = user->getUserName();

    if(!query.exec("SELECT * FROM Users WHERE username ='" + username + "'"))
        throw runtime_error("ERROR DBManager::RemoveUser() Error while searching for user");

    if (!query.first())
        result = false;
    else {
        if (query.exec("DELETE FROM Users WHERE username = '" + username + "'"))
            result = true;
        else
            throw runtime_error("ERROR DBManager::RemoveUser() Error while deleting user");
    }
    db.close();

    return result;
}

/***************************************************************************
 **                SHOWS USERS IN THE DATABASE                            **
 **************************************************************************/
void DBManager::ShowUsers() {
    if (db.open()) {
        QSqlQuery query;
        query.exec("SELECT * FROM Users");
        while (query.next()) {
            qDebug() << query.value(0).toString();
        }
    }
}

/***************************************************************************
 **                STORE TEXTBOOK IN THE DATABASE                         **
 **************************************************************************/
bool DBManager::StoreTextbook(Textbook *textbook) {

    bool result = false;

    if (!db.open())
        throw runtime_error("ERROR DBManager::StoreTextbook() Error while performing db.open()");

    // Start a new transaction
    db.transaction();

    QSqlQuery query;
    int content_id = GetNewContentId();

    if (!query.prepare("INSERT INTO Textbooks (isbn, title, publisher, author, "
                       "year, edition, description, availability, price, content_id)"
                       "VALUES (:isbn,:title,:publisher,:author, :year, :edition, "
                       ":description, :availability, :price, :content_id);"))
        throw runtime_error("ERROR DBManager::StoreTextbook() Error while preparing INSERT statement");

    query.bindValue(":isbn", textbook->getISBN());
    query.bindValue(":title", textbook->getTitle());
    query.bindValue(":publisher", textbook->getPublisher());
    query.bindValue(":author", textbook->getAuthor());
    query.bindValue(":year", textbook->getYear());
    query.bindValue(":edition", textbook->getEdition());
    query.bindValue(":description", textbook->getDescription());
    query.bindValue(":availability", int(textbook->isAvailable()));
    query.bindValue(":price", textbook->getPrice());
    query.bindValue(":content_id", content_id);

    if (query.exec())
        result = true;
    else {
        qDebug() << query.lastError().text();
        throw runtime_error("ERROR DBManager::StoreTextbook() Error while inserting textbook");
    }

    db.commit();
    db.close();

    return result;
}

/***************************************************************************
 **                STORE CHAPTER IN THE DATABASE                          **
 **************************************************************************/
bool DBManager::StoreChapter(Chapter *chapter, QString &isbn) {
    bool result = false;

    if (!db.open())
        throw runtime_error("ERROR DBManager::StoreChapter() Error while performing db.open()");

    // Start a new transaction
    db.transaction();

    QSqlQuery query;
    int content_id = GetNewContentId();

    if (!query.prepare("INSERT INTO Chapters (name, number, textbook, description, "
                       "availability, price, content_id) VALUES (:name, :number, "
                       ":textbook,:description,:availability, :price, :content_id);"))
        throw runtime_error("ERROR DBManager::StoreChapter() Error while preparing INSERT statement");

    query.bindValue(":name", chapter->getTitle());
    query.bindValue(":number", chapter->getChapterNo());
    query.bindValue(":textbook", isbn);
    query.bindValue(":description", chapter->getDescription());
    query.bindValue(":availability", int(chapter->isAvailable()));
    query.bindValue(":price", chapter->getPrice());
    query.bindValue(":content_id", content_id);

    if (query.exec())
        result = true;
    else {
        qDebug() << query.lastError().text();
        throw runtime_error("ERROR DBManager::StoreChapter() Error while inserting chapter");
    }

    db.commit();
    db.close();

    return result;
}

/***************************************************************************
 **                STORE SECTION IN THE DATABASE                          **
 **************************************************************************/
bool DBManager::StoreSection(Section *section, QString &isbn, QString &ch_number) {
    bool result = false;

    if (!db.open())
        throw runtime_error("ERROR DBManager::StoreSection() Error while performing db.open()");

    // Start a new transaction
    db.transaction();

    QSqlQuery query;
    int content_id = GetNewContentId();

    if (!query.prepare("INSERT INTO Sections (name, number, chapter, textbook, "
                       "description, availability, price, content_id) VALUES "
                       "(:name, :number, :chapter, :textbook, :description,:availability, "
                       ":price, :content_id);"))
        throw runtime_error("ERROR DBManager::StoreSection() Error while preparing INSERT statement");

    query.bindValue(":name", section->getTitle());
    query.bindValue(":number", section->getSectionNo());
    query.bindValue(":chapter", ch_number.toInt());
    query.bindValue(":textbook", isbn);
    query.bindValue(":description", section->getDescription());
    query.bindValue(":availability", int(section->isAvailable()));
    query.bindValue(":price", section->getPrice());
    query.bindValue(":content_id", content_id);

    if (query.exec())
        result = true;
    else {
        qDebug() << query.lastError().text();
        throw runtime_error("ERROR DBManager::StoreSection() Error while inserting section");
    }

    db.commit();
    db.close();

    return result;
}

bool DBManager::StoreInvoice(Invoice *invoice) {
    bool result = false;

    if (!db.open())
        throw runtime_error("ERROR DBManager::StoreInvoice() Error while performing db.open()");

    // Start a new transaction
    db.transaction();

    QSqlQuery query;

    // Add a new record to the invoices table
    if (!query.prepare("INSERT INTO Invoices (student, date_purchased) VALUES (:student, :date);"))
        throw runtime_error("ERROR DBManager::StoreInvoice() Error while preparing INSERT invoice statement");

    query.bindValue(":student", invoice->getUsername());
    query.bindValue(":date", QDateTime::fromString("yyyy-MM-dd HH:mm:ss:zzz"));

    if (!query.exec())
        throw runtime_error("ERROR DBManager::StoreInvoice() Error while inserting invoice");

    // Get the invoice id from the purchases table
    int invoice_id = query.lastInsertId().toInt();

    // For each content in the invoice, add it to the purchases table
    for(vector<int>::const_iterator iter= invoice->getContentList()->begin(); iter != invoice->getContentList()->end(); ++iter) {
        if (!query.prepare("INSERT INTO Purchases (invoice_id, content_id) VALUES(:invoice_id, :content_id);"))
            throw runtime_error("ERROR DBManager::StoreInvoice() Error while preparing INSERT purchase statement");
        query.bindValue(":invoice_id", invoice_id);
        query.bindValue(":content_id", *iter);
        if (!query.exec())
            throw runtime_error("ERROR DBManager::StoreInvoice() Error while inserting purchase");
    }

    // Commit the transaction
    db.commit();

    // Close the database
    db.close();

    return result;
}

void DBManager::RetrieveContentList (QString *username, vector<Textbook> *list) {
    if (!db.open())
        throw runtime_error("ERROR DBManager::RetrieveContentList() Error while performing db.open()");

    QSqlQuery query;

    // Make sure user is a student
    if (!query.prepare("SELECT type FROM Users WHERE username=:username;"))
        throw runtime_error("ERROR DBManager::RetrieveContentList() Error while preparing SELECT statement to look up user");

    query.bindValue(":username", *username);

    if (!query.exec())
        throw runtime_error("ERROR DBManager::RetrieveContentList() Error while performing user lookup");

    // Check if username is a Student
    if ( !query.next() || query.value(0) == "student")
        throw runtime_error("User is not a student or does not exist");

    // Get textbook list for courses the student is registered in
    if (!query.prepare("SELECT Textbooks.* FROM Class_list INNER JOIN Book_List ON Class_List.course_code = Book_List.course_code INNER JOING Textbook ON Book_List.textbook_id = Textbooks.isbn WHERE Class_List.student = :username;"))
        throw runtime_error("ERROR DBManager::RetrieveContentList() Error while preparing join statement to get user's class list");

    query.bindValue(":username", *username);

    if (!query.exec())
        throw runtime_error("ERROR DBManager::RetrieveContentList() Error while retrieving user's textbook list");

    // Loop through each textbook, getting all the chapters and sections and creating object
    while (query.next()) {

        Textbook textbook(query.value(0), query.value(1), query.value(2),
                          query.value(3), query.value(4), query.value(5),
                          query.value(6), query.value(7), query.value(8),
                          query.value(9));

        QSqlQuery ch_query;
        if (!ch_query.prepare("SELECT * FROM Chapters WHERE textbook = :isbn"))
            throw runtime_error("ERROR DBManager::RetrieveContentList() Error while preparing statement to look up chapter info");

        ch_query.bindValue(":isbn", query.value(0), );

        if (!ch_query.exec())
            throw runtime_error("ERROR DBManager::RetrieveContentList() Error while retrieving chapter info");

        while (ch_query.next()) {
            Chapter chapter(query.value(0), query.value(1), &textbook,
                            query.value(3), query.value(4), query.value(5),
                            query.value(6));
            QSqlQuery sec_query;
            if (!sec_query.prepare("SELECT * FROM Sections WHERE textbook = :isbn"))
                throw runtime_error("ERROR DBManager::RetrieveContentList() Error while preparing statement to look up section info");

            sec_query.bindValue(":isbn", query.value(0), );

            if (!sec_query.exec())
                throw runtime_error("ERROR DBManager::RetrieveContentList() Error while retrieving section info");

            while (sec_query.next()) {
                Section section(query.value(0), query.value(1), &chapter,
                                &textbook, query.value(4), query.value(5),
                                query.value(6), query.value(7));
            }
        }

        list->push_back(textbook);
    }
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
/*void viewFields(QSqlDatabase* db, QString table) {
    if (db->open()) {
        QSqlRecord rec = db->record(table);
        for (int i=0; i < rec.count(); i++) {
            qDebug() << rec.fieldName(i);
        }
    }

}*/

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
 **                NEW RECORD IN CONTENT                                  **
 **************************************************************************/
int DBManager::GetNewContentId() {
    QSqlQuery query;

    if(!query.exec("INSERT INTO Content DEFAULT VALUES;"))
        throw runtime_error("ERROR DBManager::GetNewContentId() Error while creating new content id");

    return query.lastInsertId().toInt();
}

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
