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
        for (QList<Class*>::iterator iter = this->classes.begin(); iter != this->classes.end(); ++iter) {
                delete *iter;
        }
        this->classes.clear(); // Make classes have 0 elements
        //this->user = User();

}

void LocalStorage::refresh() {
        this->cleanup();
        if (storageControl == 0)
                throw std::runtime_error("LocalStorage::refresh(), storageControl is null");
        storageControl->refreshContent(user, classes);
}

const QList<Textbook*>* LocalStorage::getTextbooks(QString courseCode) const {
    foreach(Class *c , classes){

        if (c->getCourse()->getCourseCode().compare(courseCode) == 0)
            return &c->getBooklist();

    }
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

void LocalStorage::removeCourse(Course& course) const {
        this->storageControl->removeCourse(course);
}

void LocalStorage::addCourse(const QString& semester, const QVariant& year, const QString& courseCode, const QString& courseTitle) {
        Course newCourse(courseCode, courseTitle);
        QString sem(semester + " " + year.toString());
        Class newClass(sem, newCourse);
        storageControl->addClass(newClass);
}

void LocalStorage::addTextbook(Textbook& t) const{
    //TODO CHANGE THIS FUNCTION TO CLASS
    //storageControl->addTextbook(t);
}

void LocalStorage::editTextbook(Textbook& t) const{
    storageControl->editTextbook(t);
}

void LocalStorage::deleteTextbook(Textbook& t) const{
    storageControl->removeTextbook(t);
}

void LocalStorage::addChapter(Chapter& c) const{
    storageControl->addChapter(c);
}

void LocalStorage::editChapter(Chapter& c) const{
    storageControl->editChapter(c);
}

void LocalStorage::deleteChapter(Chapter& c) const{
    storageControl->removeChapter(c);
}

void LocalStorage::addSection(Section& s) const{
    storageControl->addSection(s);
}

void LocalStorage::editSection(Section& s) const{
    storageControl->editSection(s);
}

void LocalStorage::deleteSection(Section& s) const{
    storageControl->removeSection(s);
}

