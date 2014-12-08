#include "localStorage.h"

LocalStorage::LocalStorage(const StorageControl& storageControl) : storageControl(&storageControl), user("", "") {}

LocalStorage::~LocalStorage() {
    this->cleanup();
}

const User& LocalStorage::getUser() const {
    return this->user;
}

const QList<Class*>& LocalStorage::getClasses() const {
    return this->classes;
}

void LocalStorage::cleanup() {
    // go through each course and delete it with its content

    foreach (Class *clss, classes) {
        delete clss;
    }

    this->classes.clear();

}

void LocalStorage::refresh() {
    this->cleanup();
    if (storageControl == 0)
            throw std::runtime_error("LocalStorage::refresh(), storageControl is null");
    try {
        storageControl->refreshContent(user, classes);
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

const QList<Textbook*>* LocalStorage::getTextbooks(QString courseCode) const {

    foreach(Class *c , classes)
        if (c->getCourse()->getCourseCode().compare(courseCode) == 0)
            return &c->getBooklist();

    return new QList<Textbook*>;
}

void LocalStorage::login(const QString& username, const QString& password) {
    user = User(username, password);
    try {
        this->storageControl->logIn(user);
    } catch(const std::runtime_error e) {
        throw e;
    }
}

void LocalStorage::removeClass(Class& clss) const {
    try {
        this->storageControl->removeClass(clss);
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

void LocalStorage::addCourse(const QString& semester, const QVariant& year, const QString& courseCode, const QString& courseTitle) {

    Course newCourse(courseCode, courseTitle);
    QString sem(semester + " " + year.toString());
    Class newClass(sem, newCourse);

    try {
        storageControl->addClass(newClass);
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

void LocalStorage::addTextbook(Class& c) const {
    try {
        storageControl->addTextbook(c);
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

void LocalStorage::editTextbook(Textbook& t) const {
    try {
        storageControl->editTextbook(t);
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

void LocalStorage::deleteTextbook(Textbook& t) const {
    try {
        storageControl->removeTextbook(t);
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

void LocalStorage::addChapter(Chapter& c) const {
    try {
        storageControl->addChapter(c);
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

void LocalStorage::editChapter(Chapter& c) const {
    try {
        storageControl->editChapter(c);
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

void LocalStorage::deleteChapter(Chapter& c) const {
    try {
        storageControl->removeChapter(c);
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

void LocalStorage::addSection(Section& s) const {
    try {
        storageControl->addSection(s);
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

void LocalStorage::editSection(Section& s) const {
    try {
        storageControl->editSection(s);
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

void LocalStorage::deleteSection(Section& s) const {
    try {
        storageControl->removeSection(s);
    }
    catch(std::runtime_error e) {
        throw e;
    }
}

