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

void LocalStorage::update(QList<Class*>& inClasses) {
        this->cleanup();
        this->classes = inClasses;
}

void LocalStorage::cleanup() {
        // go through each course and delete it with its content
        for (QList<Class*>::iterator iter = this->classes.begin(); iter != this->classes.end(); ++iter) {
                delete *iter;
        }
        this->classes.clear(); // Make classes have 0 elements
}

void LocalStorage::refresh() {
        if (storageControl == 0)
                throw runtime_error("LocalStorage::refresh(), storageControl is null");
        storageControl->refreshContent(user, classes);
}

void LocalStorage::login(const QString& username, const QString& password) {
        user = User(username, password);
        try {
                this->storageControl->logIn(user);
        } catch(const runtime_error e) {
                throw e;
        }
}
