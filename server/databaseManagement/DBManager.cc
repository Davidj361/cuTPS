#include "DBManager.h"

using namespace std;

/***************************************************************************
 **                INITILIZE DATABASE                                     **
 **************************************************************************/
DBManager::DBManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./../resources/cuTPS.db"); // Connect to the database
    if (!db.open())
        throw runtime_error("ERROR DBManager::DBManager() Unable to open database");
}

/***************************************************************************
 **                  DESTROY DATABASE                                     **
 **************************************************************************/
DBManager::~DBManager() {
    db.close();
}

void DBManager::AddTextbook(QString isbn, QString title, QString publisher, QString author, int year, QString edition, QString description, bool availability, float price) {
    if (isbn == "")
        throw runtime_error("ERROR DBController::AddTextbook() isbn cannot be null");

    if (title == "")
        throw runtime_error("ERROR DBController::AddTextbook() title cannot be null");

    if (publisher == "")
        throw runtime_error("ERROR DBController::AddTextbook() publisher cannot be null");

    if (author == "")
        throw runtime_error("ERROR DBController::AddTextbook() author cannot be null");

    QSqlQuery query;

    db.transaction();

    int content_id = GetNewContentId();

    if (!query.prepare("INSERT INTO Textbooks (isbn, title, publisher, author, "
                       "year, edition, description, availability, price, content_id)"
                       "VALUES (:isbn,:title,:publisher,:author, :year, :edition, "
                       ":description, :availability, :price, :content_id);"))
        throw runtime_error("ERROR DBManager::AddTextbook() Error while preparing INSERT statement");

    query.bindValue(":isbn", isbn);
    query.bindValue(":title", title);
    query.bindValue(":publisher", publisher);
    query.bindValue(":author", author);
    query.bindValue(":year", year);
    query.bindValue(":edition", edition);
    query.bindValue(":description", description);
    query.bindValue(":availability", availability);
    query.bindValue(":price", price);
    query.bindValue(":content_id", content_id);

    if (!query.exec()) {
        db.rollback();
        if (query.lastError().number() == 19)
            throw runtime_error("ERROR DBController::StoreTextbook(), Textbook already exists");
        else
            throw runtime_error("ERROR DBController::StoreTextbook() Error while inserting textbook");
    }

    db.commit();
}

int DBManager::GetNewContentId() {
    QSqlQuery query;

    if (!query.exec("INSERT INTO Content DEFAULT VALUES;"))
        throw runtime_error("ERROR DBController::GetNewContentId() Error while creating new content id");

    return query.lastInsertId().toInt();
}
