#ifndef GUARD_LOCALSTORAGECONTROLLER_H
#define GUARD_LOCALSTORAGECONTROLLER_H

#include "../../../common/headers/Class.h"
#include "../../../common/headers/Textbook.h"
#include "../../../common/headers/Chapter.h"
#include "../../../common/headers/Section.h"
#include "../../../common/headers/User.h"
#include "../../storage/StorageControl.h"
#include <QList>

class LocalStorage {
        public:
                LocalStorage(const StorageControl&);
                ~LocalStorage();
                // Add const and non-const functions
                const User& getUser() const;
                const QList<Class*>& getClasses() const;
                // this is used to update the storage for client when refresh option is used in GUI
                void refresh();
                // This is used to login, give it username and password
                void login(const QString& username, const QString& password);
                const QList<Textbook*>* getTextbooks(QString courseCode) const;
                void removeClass(Class& clss) const;
                void addCourse(const QString& semester, const QVariant& year, const QString& courseCode, const QString& courseTitle);

                // The below function should be called for every update and upon deconstruction of this controller
                void cleanup(); // Delete all the allocated data

                void addTextbook(Class&) const;
                void editTextbook(Textbook&) const;
                void deleteTextbook(Textbook&) const;
                void addChapter(Chapter&) const;
                void editChapter(Chapter&) const;
                void deleteChapter(Chapter&) const;
                void addSection(Section&) const;
                void editSection(Section&) const;
                void deleteSection(Section&) const;

        private:
                void update(QList<Class*>&);



                // For connecting to server
                const StorageControl* const storageControl;
                // We'll have a list of textbooks, and a list of chapters for the textbook, and a list of sections for the chapter
                // The list of courses will have a textbook
                User user;
                QList<Class*> classes; // Bear in mind that there's textbooks, chapters, sections in here

};


#endif
