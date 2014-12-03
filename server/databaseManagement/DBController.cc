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
    }
    catch(runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                DELETE TEXTBOOK FROM THE DATABASE                      **
 **************************************************************************/
void DBController::DeleteTextbook(Textbook *textbook) {
    try {
        dbManager->DeleteContent(textbook->getcid());
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
    }
    catch(runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                DELETE CHAPTER FROM THE DATABASE                       **
 **************************************************************************/
void DBController::DeleteChapter(Chapter *chapter) {
    try {
        dbManager->DeleteContent(chapter->getcid());
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
    }
    catch(runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                DELETE SECTION FROM THE DATABASE                       **
 **************************************************************************/
void DBController::DeleteSection(Section *section) {
    try {
        dbManager->DeleteContent(section->getcid());
    }
    catch(runtime_error e) {
        throw e;
    }
}

/***************************************************************************
 **                STORE INVOICE IN THE DATABASE                          **
 **************************************************************************/
void DBController::AddInvoice(Invoice *invoice) {
    try {
        dbManager->AddInvoice(invoice->getUsername(), invoice->getContentList());
    }
    catch(runtime_error e) {
        throw e;
    }
}

void DBController::RetrieveContentList (QString &username, QList<Class *> &list) {
    try {
        dbManager->RetrieveContentList(username, list);
    }
    catch(runtime_error e) {
        throw e;
    }
}
