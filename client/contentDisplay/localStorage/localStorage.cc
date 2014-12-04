#include "localStorage.h"

LocalStorage::~LocalStorage() {
        this->cleanup();
}

const User& LocalStorage::getUser() const {
        return this->user;
}

const QList<Class*>& LocalStorage::getClasses() const {
        return this->classes;
}

void LocalStorage::update(User& inUser, QList<Class*>& inClasses) {
        this->cleanup();
        this->classes = inClasses;
        this->user = inUser;
}

void LocalStorage::cleanup() {
        // go through each course and delete it with its content
        for (QList<Class*>::iterator iter = this->classes.begin(); iter != this->classes.end(); ++iter) {
                delete *iter;
        }
        this->classes.clear(); // Make classes have 0 elements
}
