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
            throw runtime_error("ERROR DBManager::AddTextbook(), Textbook already exists");
        else
            throw runtime_error("ERROR DBManager::AddTextbook() Error while inserting textbook");
    }

    db.commit();
}

void DBManager::EditTextbook(QString isbn, QString title, QString publisher, QString author, int year, QString edition, QString description, bool availability, float price, int content_id) {
    if (isbn == "")
        throw runtime_error("ERROR DBManager::EditTextbook() isbn cannot be empty");

    if (title == "")
        throw runtime_error("ERROR DBManager::EditTextbook() title cannot be empty");

    if (publisher == "")
        throw runtime_error("ERROR DBManager::EditTextbook() publisher cannot be empty");

    if (author == "")
        throw runtime_error("ERROR DBManager::EditTextbook() author cannot be empty");

    QSqlQuery query;

    db.transaction();

    if (!query.prepare("UPDATE Textbook SET isbn = :isbn, title = :title, publisher = :publisher, author = :author,"
                       "year = :year, edition = :edition, description = :description, availability = :availability "
                       "price = :price WHERE content_id = :content_id;"))
        throw runtime_error("ERROR DBManager::EditTextbook() Error while preparing INSERT statement");

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
            throw runtime_error("ERROR DBManager::EditTextbook(), Textbook with that isbn already exists");
        else
            throw runtime_error("ERROR DBManager::EditTextbook() Error while inserting textbook");
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
            throw runtime_error("ERROR DBManager::AddChapter(), Chapter already exists");
        else
            throw runtime_error("ERROR DBManager::AddChapter() Error while inserting chapter");
    }

    db.commit();
}

void DBManager::EditChapter(QString title, int chapter, QString textbook, QString description, bool available, float price, int content_id) {
    if (title == "")
        throw runtime_error("ERROR DBManager::EditChapter() title cannot be empty");

    if (textbook == "")
        throw runtime_error("ERROR DBManager::EditChapter() textbook cannot be empty");

    QSqlQuery query;

    db.transaction();

    if (query.prepare("UPDATE Chapters SET name = :name, number = :number, textbook = :textbook, description = :description, "
                      "availability = :availability, price = :price WHERE content_id = :content_id;"))
        throw runtime_error("ERROR DBManager::EditChapter() Error while preparing UPDATE statement");

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
            throw runtime_error("ERROR DBManager::EditChapter(), Chapter already exists");
        else
            throw runtime_error("ERROR DBManager::EditChapter() Error while updating chapter");
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
            throw runtime_error("ERROR DBManager::AddSection(), Section already exists");
        else
            throw runtime_error("ERROR DBManager::AddSection() Error while inserting section");
    }

    db.commit();
}

void DBManager::EditSection(QString title, int section, int chapter, QString textbook, QString description, bool available, float price, int content_id) {
    if (title == "")
        throw runtime_error("ERROR DBManager::EditSection() title cannot be empty");

    if (textbook == "")
        throw runtime_error("ERROR DBManager::EditSection() textbook cannot be empty");

    QSqlQuery query;

    db.transaction();

    if (query.prepare("UPDATE Sections SET name = :name, number = :number, chapter = :chapter, textbook = :textbook, description = :description "
                      " availability = :availability, price = :price WHERE content_id = :content_id;"))
        throw runtime_error("ERROR DBManager::EditSection() Error while preparing UPDATE statement");

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
            throw runtime_error("ERROR DBManager::EditSection(), Section already exists");
        else
            throw runtime_error("ERROR DBManager::EditSection() Error while updating section");
    }

    db.commit();
}

void DBManager::DeleteContent(int content_id) {
    QSqlQuery query;

    db.transaction();

    if (!query.prepare("DELETE FROM Content WHERE id = :content_id;"))
        throw runtime_error("ERROR DBManager::DeleteContent() Error while preparing DELETE statement");

    query.bindValue(":content_id", content_id);

    if (!query.exec()) {
        db.rollback();
        throw runtime_error("ERROR DBManager::DeleteContent() Error while executing DELETE statement");
    }
    db.commit();
}

void DBManager::AddCourse(QString coursecode, QString coursetitle) {
    if (coursecode == "null")
        throw runtime_error("ERROR DBManager::AddCourse() course code cannot be empty");

    if (coursetitle == "null")
        throw runtime_error("ERROR DBManager::AddCourse() course title cannot be empty");

    QSqlQuery query;

    db.transaction();

    if (!query.prepare("INSERT INTO Courses (code, name)"
                       "VALUES (:code, :name);"))
        throw runtime_error("ERROR DBManager::AddCourse() Error while preparing INSERT statement");

    query.bindValue(":code", coursecode);
    query.bindValue(":name", coursetitle);

    if (!query.exec()) {
        db.rollback();
        if (query.lastError().number() == 19)
            throw runtime_error("ERROR DBManager::AddCourse(), Course already exists");
        else
            throw runtime_error("ERROR DBManager::AddCourse() Error while inserting course");
    }

    db.commit();
}

void DBManager::EditCourse(QString coursecode, QString coursetitle, QString newcoursecode) {
    if (coursecode == "")
        throw runtime_error("ERROR DBManager::EditCourse() course code cannot be empty");

    if (coursetitle == "")
        throw runtime_error("ERROR DBManager::EditCourse() course title cannot be empty");

    QSqlQuery query;

    db.transaction();

    if (query.prepare("UPDATE Courses SET code = :newcode, name = :name WHERE code = :code;"))
        throw runtime_error("ERROR DBManager::EditCourse() Error while preparing UPDATE statement");

    query.bindValue(":newcode", newcoursecode.isEmpty() ? coursecode : newcoursecode);
    query.bindValue(":name", coursetitle);
    query.bindValue(":code", coursecode);

    if (!query.exec()) {
        db.rollback();
        if (query.lastError().number() == 19)
            throw runtime_error("ERROR DBManager::EditCourse(), Course already exists");
        else
            throw runtime_error("ERROR DBManager::EditCourse() Error while updating course");
    }

    db.commit();
}

void DBManager::DeleteCourse(QString coursecode) {
    if (coursecode == "null")
        throw runtime_error("ERROR DBManager::DeleteClass() Course code cannot be empty");

    QSqlQuery query;

    db.transaction();

    if (!query.prepare("DELETE FROM Courses WHERE code = :code;"))
        throw runtime_error("ERROR DBManager::DeleteCourse() Error while preparing DELETE statement");

    query.bindValue(":code", coursecode);

    if (!query.exec()) {
        db.rollback();
        throw runtime_error("ERROR DBManager::DeleteCourse() Error while executing DELETE statement");
    }
    db.commit();
}

void DBManager::AddClass(QString course, QString semester) {
    if (course == "null")
        throw runtime_error("ERROR DBManager::AddClass() Course code cannot be empty");

    if (semester == "null")
        throw runtime_error("ERROR DBManager::AddClass() Semester cannot be empty");

    QSqlQuery query;

    db.transaction();

    if (!query.prepare("INSERT INTO Classes (course, semester)"
                       "VALUES (:course, :semester);"))
        throw runtime_error("ERROR DBManager::AddClass() Error while preparing INSERT statement");

    query.bindValue(":course", course);
    query.bindValue(":semester", semester);

    if (!query.exec()) {
        db.rollback();
        if (query.lastError().number() == 19)
            throw runtime_error("ERROR DBManager::AddClass(), Class already exists");
        else
            throw runtime_error("ERROR DBManager::AddClass() Error while inserting Class");
    }

    db.commit();
}

void DBManager::DeleteClass(QString course, QString semester) {
    if (course == "null")
        throw runtime_error("ERROR DBManager::DeleteClass() Course code cannot be empty");

    if (semester == "null")
        throw runtime_error("ERROR DBManager::DeleteClass() Semester cannot be empty");

    QSqlQuery query;

    db.transaction();

    if (!query.prepare("DELETE FROM Classes WHERE course = :course AND semester = :semester;"))
        throw runtime_error("ERROR DBManager::DeleteClass() Error while preparing DELETE statement");

    query.bindValue(":course", course);
    query.bindValue(":semester", semester);

    if (!query.exec()) {
        db.rollback();
        throw runtime_error("ERROR DBManager::DeleteClass() Error while executing DELETE statement");
    }
    db.commit();
}

void DBManager::AddStudentsToClass (QList<Student *> &list, QString course, QString semester) {
    if (list.empty())
        throw runtime_error("ERROR DBManager::AddStudentsToClass() list of Students cannot be empty");

    QSqlQuery query;

    db.transaction();

    Student *student;
    foreach (student, list) {
        if (!query.prepare("INSERT INTO Class_List (student, semester, course)"
                           "VALUES (:student, :semester, :course);"))
            throw runtime_error("ERROR DBManager::AddStudentsToClass() Error while preparing INSERT statement");

        query.bindValue(":student", student->getUsername());
        query.bindValue(":course", course);
        query.bindValue(":semester", semester);

        if (!query.exec()) {
            db.rollback();
            if (query.lastError().number() == 19)
                throw runtime_error("ERROR DBManager::AddStudentsToClass(), Student already registerd in class");
            else
                throw runtime_error("ERROR DBManager::AddStudentsToClass() Error while adding studen to class");
        }
    }
    db.commit();
}

void DBManager::RemoveStudentsFromClass(QList<Student *> &list, QString course, QString semester) {
    if (list.empty())
        throw runtime_error("ERROR DBManager::RemoveStudentsFromClass() list of Students cannot be empty");

    QSqlQuery query;

    db.transaction();

    Student *student;
    foreach (student, list) {
        if (!query.prepare("DELETE FROM Class_List WHERE student = :student, semester = :semester, course = :course;"))
            throw runtime_error("ERROR DBManager::RemoveStudentsFromClass() Error while preparing DELETE statement");

        query.bindValue(":student", student->getUsername());
        query.bindValue(":course", course);
        query.bindValue(":semester", semester);

        if (!query.exec()) {
            db.rollback();
            throw runtime_error("ERROR DBManager::RemoveStudentsFromClass() Error while adding student to class");
        }
    }
    db.commit();
}

void DBManager::AddTextbooksToClass (QList<Textbook *> &list, QString course, QString semester) {
    if (list.empty())
        throw runtime_error("ERROR DBManager::AddTextbooksToClass() list of Textbooks cannot be empty");

    QSqlQuery query;

    db.transaction();

    Textbook *textbook;
    foreach (textbook, list) {
        if (!query.prepare("INSERT INTO Book_List (textbook_id, semester, course)"
                           "VALUES (:textbook, :semester, :course);"))
            throw runtime_error("ERROR DBManager::AddTextbooksToClass() Error while preparing INSERT statement");

        query.bindValue(":textbook", textbook->getISBN());
        query.bindValue(":course", course);
        query.bindValue(":semester", semester);

        if (!query.exec()) {
            db.rollback();
            if (query.lastError().number() == 19)
                throw runtime_error("ERROR DBManager::AddTextbooksToClass(), Textbook already registerd in class");
            else
                throw runtime_error("ERROR DBManager::AddTextbooksToClass() Error while adding textbook to class");
        }
    }
    db.commit();
}

void DBManager::RemoveTextbooksFromClass(QList<Textbook *> &list, QString course, QString semester) {
    if (list.empty())
        throw runtime_error("ERROR DBManager::RemoveTextbooksFromClass() list of Textbooks cannot be empty");

    QSqlQuery query;

    db.transaction();

    Textbook *textbook;
    foreach (textbook, list) {
        if (!query.prepare("DELETE FROM Book_List WHERE textbook_id = :textbook, semester = :semester, course = :course;"))
            throw runtime_error("ERROR DBManager::RemoveTextbooksFromClass() Error while preparing DELETE statement");

        query.bindValue(":textbook", textbook->getISBN());
        query.bindValue(":course", course);
        query.bindValue(":semester", semester);

        if (!query.exec()) {
            db.rollback();
            throw runtime_error("ERROR DBManager::RemoveTextbooksFromClass() Error while adding student to class");
        }
    }
    db.commit();
}

void DBManager::AddInvoice(QString username, QList<int> cart) {
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
    foreach(int content_id , cart) {

        // Get the price of the content being added
        if (!query.prepare("SELECT price FROM textbooks WHERE content_id = :t_id UNION"
                           "SELECT price FROM chapters WHERE content_id = :c_id UNION"
                           "SELECT price FROM sections WHERE content_id = :s_id;"))
            throw runtime_error("ERROR DBManager::AddInvoice() Error while prepraing SELECT price query");

        // Bind the content id to the query
        query.bindValue(":t_id", content_id);
        query.bindValue(":c_id", content_id);
        query.bindValue(":s_id", content_id);

        if (!query.exec()) {
            db.rollback();
            throw runtime_error("ERROR DBManager::AddInvoice() Error while retrieving content price");
        }

        if (!query.first())
            throw runtime_error("ERROR DBManager::AddInvoice() Unable to find content id " + content_id);

        float price = query.value(0).toFloat();

        query.clear();

        if (!query.prepare("INSERT INTO Purchases (invoice_id, content_id, purchase_price) VALUES(:invoice_id, :content_id, :purchase_price);"))
            throw runtime_error("ERROR DBManager::AddInvoice() Error while preparing INSERT purchase statement");
        query.bindValue(":invoice_id", invoice_id);
        query.bindValue(":content_id", content_id);
        query.bindValue(":purchase_price", price);

        if (!query.exec())
            throw runtime_error("ERROR DBManager::AddInvoice() Error occurred while inserting purchase");

        query.clear();
    }

    db.commit();
}

void DBManager::RetrieveContentList(QString username, QList<Class *> &list) {
    if (username == "")
        throw runtime_error("ERROR DBManager::RetrieveContentList() username cannot be empty");

    QSqlQuery query;
    QString userType = "";

    // Get user from db
    if (!query.exec("SELECT type FROM Users WHERE username='" + username + "'"))
        throw runtime_error("ERROR DBController::RetrieveContentList()  Error while performing user lookup");

    // Check if user is a student or content manager
    if ( !query.first() || (query.value(0) != "student" && query.value(0) != "content_manager") )
        throw runtime_error("User is not a student or content manager or does not exist");

    userType = query.value(0).toString();

    if (userType == "student")
        GetClassesForStudent(list, username);
    else
        GetAllClasses(list);

    Class *clss;
    foreach (clss, list) {
        GetTextbooksForClass(clss->getBooklist(), clss->getCourse()->getCourseCode(), clss->getSemester());

        Textbook *textbook;
        foreach (textbook, clss->getBooklist()) {
            GetChaptersForTextbook(textbook->getChapters(), textbook);

            Chapter *chapter;
            foreach (chapter, textbook->getChapters()) {
                GetSectionsForChapter(chapter->getSections(), textbook, chapter);
            }
        }
    }
}

void DBManager::GetClassesForStudent(QList<Class *> &list, QString username) {
    QSqlQuery query;

    if (!query.prepare("SELECT Courses.*, Classes.semester FROM Classes INNER JOIN Courses ON Classes.course = Courses.code "
                       "NATURAL JOIN Class_List WHERE Class_List.student = :username"))
        throw runtime_error("ERROR DBController::GetClassesForStudent() Error while preparing join statement to get student's class list");

    query.bindValue(":username", username);

    if (!query.exec())
        throw runtime_error("ERROR DBController::GetClassesForStudent() Error while retrieving students's textbook list");

    while (query.next()) {
        Course *course = new Course(query.value(0).toString(),
                                    query.value(1).toString());

        Class *clss = new Class(query.value(2).toString(), course);

        list.append(clss);
    }
}

void DBManager::GetAllClasses(QList<Class *> &list) {
    QSqlQuery query;

    if (!query.prepare("SELECT Courses.*, Classes.semester FROM Classes INNER JOIN Courses ON Classes.course = Courses.code"))
        throw runtime_error("ERROR DBController::GetAllClasses() Error while preparing join statement to get student's class list");

    if (!query.exec())
        throw runtime_error("ERROR DBController::GetAllClasses() Error while retrieving students's textbook list");

    while (query.next()) {
        Course *course = new Course(query.value(0).toString(),
                                    query.value(1).toString());

        Class *clss = new Class(query.value(2).toString(), course);

        list.append(clss);
    }
}

void DBManager::GetTextbooksForClass(QList<Textbook *> &list, QString course, QString semester) {
    QSqlQuery query;

    // Get textbook list for courses the student is registered in
    if (!query.prepare("SELECT Textbooks.* FROM Textbooks INNER JOIN Book_List ON Book_List.textbook_id = Textbooks.isbn WHERE Book_List.semester = :semester AND Book_List.course = :course"))
        throw runtime_error("ERROR DBController::GetContentManagerBookList() Error while preparing query to select textbooks in a class");

    query.bindValue(":semester", semester);
    query.bindValue(":course", course);

    if (!query.exec())
        throw runtime_error("ERROR DBController::GetTextbooksForClass() Error while retrieving textbooks for class");

    while (query.next()) {
        Textbook *textbook = new Textbook(query.value(0).toString(), // ISBN
                                          query.value(1).toString(), // Title
                                          query.value(2).toString(), // Publisher
                                          query.value(3).toString(), // Author
                                          query.value(4).toInt(),    // year
                                          query.value(5).toString(), // Edition
                                          query.value(6).toString(), // Description
                                          query.value(7).toBool(),  // Availability
                                          query.value(8).toFloat(), // Price
                                          query.value(9).toInt());  // Content ID
        list.append(textbook);
    }
}

void DBManager::GetChaptersForTextbook(QList<Chapter *> &list, Textbook *textbook) {
    QSqlQuery ch_query;

    if (!ch_query.prepare("SELECT * FROM Chapters WHERE textbook = :isbn AND availability = 1;"))
        throw runtime_error("ERROR DBController::GetChaptersForTextbook() Error while preparing statement to look up chapter info");

    ch_query.bindValue(":isbn", textbook->getISBN());

    if (!ch_query.exec())
        throw runtime_error("ERROR DBController::GetChaptersForTextbook() Error while retrieving chapter info");

    while (ch_query.next()) {
        Chapter *chapter = new Chapter(ch_query.value(0).toString(),  // Name
                                       ch_query.value(1).toInt(),     // Chapter Number
                                       textbook,                      // Textbook
                                       ch_query.value(3).toString(),  // Description
                                       ch_query.value(4).toBool(),    // Availability
                                       ch_query.value(5).toFloat(),   // Price
                                       ch_query.value(6).toInt());    // Content ID
        list.append(chapter);
    }
}

void DBManager::GetSectionsForChapter(QList<Section *> &list, Textbook *textbook, Chapter *chapter) {
    QSqlQuery sec_query;

    if (!sec_query.prepare("SELECT * FROM Sections WHERE textbook = :isbn AND chapter = :chapter AND availability = 1;"))
        throw runtime_error("ERROR DBController::GetSectionsForChapter() Error while preparing statement to look up section info");

    sec_query.bindValue(":isbn", textbook->getISBN());
    sec_query.bindValue(":chapter", chapter->getChapterNo());

    if (!sec_query.exec())
        throw runtime_error("ERROR DBController::GetSectionsForChapter() Error while retrieving section info");

    while (sec_query.next()) {
        Section *section = new Section(sec_query.value(0).toString(),  // Name
                                       sec_query.value(1).toInt(),     // Section Number
                                       chapter,                       // Chapter
                                       textbook,                      // Textbook
                                       sec_query.value(4).toString(),  // Description
                                       sec_query.value(5).toBool(),    // Availability
                                       sec_query.value(6).toFloat(),   // Price
                                       sec_query.value(7).toInt());    // Content ID

        list.append(section);
    }
}

int DBManager::GetNewContentId() {
    QSqlQuery query;

    if (!query.exec("INSERT INTO Content DEFAULT VALUES;"))
        throw runtime_error("ERROR DBManager::GetNewContentId() Error while creating new content id");

    return query.lastInsertId().toInt();
}
