#ifndef GUARD_LOCALSTORAGECONTROLLER_H
#define GUARD_LOCALSTORAGECONTROLLER_H

#include "../../../common/headers/Textbook.h"
#include "../../../common/headers/Chapter.h"
#include "../../../common/headers/Section.h"
#include "../../../common/headers/User.h"
#include "../../../common/headers/Class.h"
#include <QList>

class LocalStorage {
        public:
                ~LocalStorage();
                // Add const and non-const functions
                const User& getUser() const;
                const QList<Class*>& getClasses() const;
                void update(User&, QList<Class*>&);
        private:
                // We'll have a list of textbooks, and a list of chapters for the textbook, and a list of sections for the chapter
                // The list of courses will have a textbook
                User user;
                QList<Class*> classes; // Bear in mind that there's textbooks, chapters, sections in here

                // The below function should be called for every update and upon deconstruction of this controller
                void cleanup(); // Delete all the allocated data 
};


#endif
