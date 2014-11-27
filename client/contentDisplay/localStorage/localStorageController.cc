#include "localStorageController.h"

LocalStorageController::~LocalStorageController() {
        this->cleanup();
}

const User& LocalStorageController::getUser() const {
        return this->user;
}

const QList<Course*>& LocalStorageController::getCourses() const {
        return this->courses;
}

void LocalStorageController::update(User& inUser, QList<Course*>& inCourses) {
        this->cleanup();
        this->courses = inCourses;
        this->user = inUser;
}

void LocalStorageController::cleanup() {
        // go through each course and delete it with its content
        for (QList<Course*>::iterator iter = this->courses.begin(); iter != this->courses.end(); ++iter) {
                delete *iter;
        }
        this->courses.clear(); // Make courses have 0 elements
}
