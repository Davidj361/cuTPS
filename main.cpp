#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlTableModel>


/***************************************************************************
 **                ADD A USER TO DATABASE                                 **
 **************************************************************************/
void addUser(QSqlDatabase* db) {
    if (db->open()) {
        QSqlQuery query;
        query.exec(QString("INSERT INTO Users VALUES ('admin1','pass','administrator','j smith'"));   // INSERT USER admin1 TO TABLE Users
        QSqlRecord rec;
        if (query.exec("SELECT * FROM users")) {    // GET ALL FIELDS AND VALUES FROM TABLE Users
            rec = query.record();
            qDebug() << rec.count();  // returns 4, displaying only field names
            qDebug() << query.size(); // Should return 1, currently displaying -1
        }

        qDebug() << db->record("Users");

    }
    else {
        qDebug() << "Cannot open the database at the addUser level";
        }
}

/***************************************************************************
 **                DISPLAYS THE NAMES OF TABLES IN DATABASE               **
 **************************************************************************/
void displayTables(QSqlDatabase* db) {
    for (int i=0; i < db->tables().size(); i++)
        qDebug() << db->tables().at(i);
}


int main(int argc, char *argv[])
{
    const char* charstr = "admin";
    QString str = charstr;
    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/student/dbmanager/cuTPS.db");

    if (db.open()) {
        displayTables(&db);
        addUser(&db);
        db.close();
    }


    return a.exec();
}

