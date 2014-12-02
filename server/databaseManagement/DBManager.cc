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

QString DBManager::Login(QString username, QString password) {
    if (username == "")
        throw runtime_error("ERROR DBManager::Login() username cannot be empty");
    if (password == "")
        throw runtime_error("ERROR DBManager::Login() password cannot be empty");

    QSqlQuery query;

    if (!query.prepare("SELECT type FROM Users WHERE username=:username AND password=:password;"))
        throw runtime_error("ERROR DBManager::Login() Error while preparing user login lookup");

    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec())
        throw runtime_error("ERROR DBManager::Login() Error while searching for user");

    if (!query.first())
        throw runtime_error("ERROR DBManager::Login() Incorrect username or password");

    return query.value(0).toString();
}

void DBManager::AddTextbook(QString isbn, QString title, QString publisher, QString author, int year, QString edition, QString description, bool availability, float price) {
    if (isbn == "")
        throw runtime_error("ERROR DBManager::AddTextbook() isbn cannot be empty");

    if (title == "")
        throw runtime_error("ERROR DBManager::AddTextbook() title cannot be empty");

    if (publisher == "")
        throw runtime_error("ERROR DBManager::AddTextbook() publisher cannot be empty");

    if (author == "")
        throw runtime_error("ERROR DBManager::AddTextbook() author cannot be empty");

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
            throw runtime_error("ERROR DBManager::StoreTextbook(), Textbook already exists");
        else
            throw runtime_error("ERROR DBManager::StoreTextbook() Error while inserting textbook");
    }

    db.commit();
}

void DBManager::AddChapter(QString title, int chapter, QString textbook, QString description, bool available, float price) {
    if (title == "")
        throw runtime_error("ERROR DBManager::AddChapter() title cannot be empty");

    if (textbook == "")
        throw runtime_error("ERROR DBManager::AddChapter() textbook cannot be empty");

    QSqlQuery query;

    db.transaction();

    int content_id = GetNewContentId();

    if (query.prepare("INSERT INTO Chapters (name, number, textbook, description, "
                                             "availability, price, content_id) VALUES (:name, :number, "
                                             ":textbook,:description,:availability, :price, :content_id);"))
        throw runtime_error("ERROR DBManager::AddChapter() Error while preparing INSERT statement");

        query.bindValue(":name", title);
        query.bindValue(":number", chapter);
        query.bindValue(":textbook", textbook);
        query.bindValue(":description", description);
        query.bindValue(":availability", available);
        query.bindValue(":price", price);
        query.bindValue(":content_id", content_id);

    if (!query.exec()) {
        db.rollback();
        if (query.lastError().number() == 19)
            throw runtime_error("ERROR DBManager::StoreChapter(), Chapter already exists");
        else
            throw runtime_error("ERROR DBManager::StoreChapter() Error while inserting chapter");
    }

    db.commit();
}

void DBManager::AddSection(QString title, int section, int chapter, QString textbook, QString description, bool available, float price) {
    if (title == "")
        throw runtime_error("ERROR DBManager::AddSection() title cannot be empty");

    if (textbook == "")
        throw runtime_error("ERROR DBManager::AddSection() textbook cannot be empty");

    QSqlQuery query;

    db.transaction();

    int content_id = GetNewContentId();

    if (query.prepare("INSERT INTO Sections (name, number, chapter, textbook, "
                                            "description, availability, price, content_id) VALUES "
                                            "(:name, :number, :chapter, :textbook, :description,:availability, "
                                            ":price, :content_id);"))
        throw runtime_error("ERROR DBManager::AddSection() Error while preparing INSERT statement");

    query.bindValue(":name", title);
    query.bindValue(":number", section);
    query.bindValue(":chapter", chapter);
    query.bindValue(":textbook", textbook);
    query.bindValue(":description", description);
    query.bindValue(":availability", available);
    query.bindValue(":price", price);
    query.bindValue(":content_id", content_id);

    if (!query.exec()) {
        db.rollback();
        if (query.lastError().number() == 19)
            throw runtime_error("ERROR DBManager::StoreSection(), Section already exists");
        else
            throw runtime_error("ERROR DBManager::StoreSection() Error while inserting section");
    }

    db.commit();
}

void DBManager::AddInvoice(QString username, vector<int> cart) {
    if (username == "")
        throw runtime_error("ERROR DBManager::AddInvoice() username cannot be empty");

    if (cart.size() == 0)
        throw runtime_error("ERROR DBManager::AddInvoice() cart cannot be empty");

    db.transaction();

    QSqlQuery query;

    // Add a new record to the invoices table
    if (!query.prepare("INSERT INTO Invoices (student, date_purchased) VALUES (:student, :date);"))
        throw runtime_error("ERROR DBManager::AddInvoice() Error while preparing INSERT invoice statement");

    query.bindValue(":student", username);
    query.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz"));

    if (!query.exec()) {
        db.rollback();
        throw runtime_error("ERROR DBManager::AddInvoice() Error while inserting invoice");
    }

    // Get the invoice id from the purchases table
    int invoice_id = query.lastInsertId().toInt();

    query.clear();

    // For each content in the invoice, add it to the purchases table
    for (vector<int>::const_iterator iter = cart.begin(); iter != cart.end(); ++iter) {

        // Get the price of the content being added
        if (!query.prepare("SELECT price FROM textbooks WHERE content_id = :t_id UNION"
                           "SELECT price FROM chapters WHERE content_id = :c_id UNION"
                           "SELECT price FROM sections WHERE content_id = :s_id;"))
            throw runtime_error("ERROR DBManager::AddInvoice() Error while prepraing SELECT price query");

        // Bind the content id to the query
        query.bindValue(":t_id", *iter);
        query.bindValue(":c_id", *iter);
        query.bindValue(":s_id", *iter);

        if (!query.exec()) {
            db.rollback();
            throw runtime_error("ERROR DBManager::AddInvoice() Error while retrieving content price");
        }

        if (!query.first())
            throw runtime_error("ERROR DBManager::AddInvoice() Unable to find content id " + *iter);

        float price = query.value(0).toFloat();

        query.clear();

        if (!query.prepare("INSERT INTO Purchases (invoice_id, content_id, purchase_price) VALUES(:invoice_id, :content_id, :purchase_price);"))
            throw runtime_error("ERROR DBManager::AddInvoice() Error while preparing INSERT purchase statement");
        query.bindValue(":invoice_id", invoice_id);
        query.bindValue(":content_id", *iter);
        query.bindValue(":purchase_price", price);

        if (!query.exec())
            throw runtime_error("ERROR DBManager::AddInvoice() Error occurred while inserting purchase");

        query.clear();
    }

    db.commit();
}

int DBManager::GetNewContentId() {
    QSqlQuery query;

    if (!query.exec("INSERT INTO Content DEFAULT VALUES;"))
        throw runtime_error("ERROR DBManager::GetNewContentId() Error while creating new content id");

    return query.lastInsertId().toInt();
}
