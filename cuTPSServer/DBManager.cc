#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QSqlRecord>
#include <QList>
#include "headers/DBManager.h"
#include "../common/headers/User.h"
#include <QDir>

QSqlDatabase db;

/***************************************************************************
 **                INITILIZE DATABASE                                     **
 **************************************************************************/
DBManager::DBManager() {
    db = QSqlDatabase::addDatabase("QSQLITE"); // Treat it as QSQLite
    //db.setDatabaseName("/home/student/cuTPS/resources/cuTPS.db"); // Connect to the database
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
bool DBManager::addUser(User* user) {
    if (db.open()) {
        QString username = user->getUserName();
        QString password = user->getPassword();
        QString type = user->getType();
        QString name = user->getName();
        QSqlQuery query;
        query.exec("SELECT * FROM Users WHERE username = '"+username+"'");

        if (query.first()) {    // GET username FIELDS AND VALUES FROM TABLE Users
            qDebug() << name << "already exists in database";
            db.close();
            return false;
        } else {
            query.prepare("INSERT INTO Users VALUES (:username,:password,:type,:name)");
            query.bindValue(":username", username);
            query.bindValue(":password", password);
            query.bindValue(":type", type);
            query.bindValue(":name", name);
            query.exec();
            qDebug() << name << "was added successfully";
            db.close();
            return true;
            //qDebug() << userToAdd + " was added";
        }
    }
}

/***************************************************************************
 **                REMOVE A USER TO DATABASE                              **
 **************************************************************************/
bool DBManager::removeUser(User* user) {

    if (db.open()){
        QSqlQuery query;
        query.exec("SELECT * FROM Users WHERE username ='"+user->getUserName()+"'");
        if (query.first()) {
            query.exec("DELETE FROM Users WHERE username = '"+user->getUserName()+"'");
            qDebug() << user->getName() << " was removed";
            return true;
        } else {
            qDebug() << user->getName() << " does not exist in the database" << endl;
        }
        db.close();
    }
    return false;
}

/***************************************************************************
 **                SHOWS USERS IN THE DATABASE                            **
 **************************************************************************/
void DBManager::showUsers() {
    if (db.open()) {
        QSqlQuery query;
        query.exec("SELECT * FROM Users");
        while (query.next()) {
            qDebug() << query.value(0).toString();
        }
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
/*int addNewContentId(QSqlDatabase* db, QString type) {
    if (db->open()) {
        QSqlQuery query;
        query.exec("INSERT INTO Content (type)" "VALUES ('"+type+"')");
        return query.lastInsertId().toInt(); // Return the ID that was added
    }
    return -1;
} */

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



/*#include "headers/DBManager.h"

using namespace std;

DBManager::DBManager () {
}

DBManager::~DBManager () {
}

int DBManager::RetrieveContentList (string *username, vector<string> *list) {
  return 0;
}

int StoreContent (string *content) {
  return 0;
}

int StoreInvoice (string *content) {
  return 0;
}
*/
