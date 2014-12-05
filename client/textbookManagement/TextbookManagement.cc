#include "TextbookManagement.h"

using namespace std;

TextbookManagement::TextbookManagement(StorageControl *storageControl) {
    this->storageControl = storageControl;
}

TextbookManagement::~TextbookManagement() {
}

void TextbookManagement::addTextbook(QString semester, QString coursecode, QString isbn, QString title, QString publisher, QString author, int year, QString edition, QString description, bool available, float price) {
    Class clss(semester, new Course(coursecode, ""));
    Textbook textbook(isbn, title, publisher, author, year, edition, description, available, price);
    clss.addTextbook(&textbook);
    storageControl->addTextbook(clss);
}

void TextbookManagement::editTextbook(QString isbn, QString title, QString publisher, QString author, int year, QString edition, QString description, bool available, float price, int content_id) {
    Textbook textbook(isbn, title, publisher, author, year, edition, description, available, price, content_id);
    storageControl->editTextbook(textbook);
}

void TextbookManagement::deleteTextbook(int content_id) {
    Textbook textbook("", "", "", "", -1, "", "", false, -1, content_id);
    storageControl->removeTextbook(textbook);
}

void TextbookManagement::addChapter(QString title, int chapterNo, QString isbn, QString description, bool available, float price) {
    Textbook textbook(isbn, "", "", "", -1, "", "", false, -1);
    Chapter chapter(title, chapterNo, &textbook, description, available, price);
    storageControl->addChapter(chapter);
}

void TextbookManagement::editChapter(QString title, int chapterNo, QString isbn, QString description, bool available, float price, int content_id) {
    Textbook textbook(isbn, "", "", "", -1, "", "", false, -1);
    Chapter chapter(title, chapterNo, &textbook, description, available, price, content_id);
    storageControl->editChapter(chapter);
}

void TextbookManagement::deleteChapter(int content_id) {
    Chapter chapter("", -1, 0, "", false, content_id);
    storageControl->removeChapter(chapter);
}

void TextbookManagement::addSection(QString title, int sectionNo, int chapterNo, QString isbn, QString description, bool available, float price) {
    Textbook textbook(isbn, "", "", "", -1, "", "", false, -1);
    Chapter chapter("", chapterNo, &textbook, "", false, -1);
    Section section(title, sectionNo, &chapter, &textbook, description, available, price);
    storageControl->addSection(section);
}

void TextbookManagement::editSection(QString title, int sectionNo, int chapterNo, QString isbn, QString description, bool available, float price, int content_id) {
    Textbook textbook(isbn, "", "", "", -1, "", "", false, -1);
    Chapter chapter("", chapterNo, &textbook, "", false, -1);
    Section section(title, sectionNo, &chapter, &textbook, description, available, price, content_id);
    storageControl->editSection(section);
}

void TextbookManagement::deleteSection(int content_id) {
    Section section("", -1, 0, 0, "", false, -1, content_id);
    storageControl->removeSection(section);
}
