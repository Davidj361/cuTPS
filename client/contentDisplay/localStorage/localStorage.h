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

                /* =====================================================================
                   Function  : Refresh
                   Purpose   : Refreshes the list of content based on the user
                   Returns   : void
                ===================================================================== */
                void refresh();

                /* =====================================================================
                   Function  : Login
                   Purpose   : Try and login
                   Returns   : void, throws error if it fails
                ===================================================================== */
                void login(const QString& username, const QString& password);

                /* =====================================================================
                   Function  : GetTextbooks
                   Purpose   : based on a courseCode, get the related textbooks
                   Returns   : QList<Textbook*> or exception
                ===================================================================== */
                const QList<Textbook*>* getTextbooks(QString courseCode) const;

                /* =====================================================================
                   Function  : Add, edit remove functions
                   Purpose   : update localstorage and persistent storage
                   Returns   : void or exception
                ===================================================================== */
                void removeClass(Class& clss) const;
                void addCourse(const QString& semester, const QVariant& year, const QString& courseCode, const QString& courseTitle);
                void addTextbook(Class&) const;
                void editTextbook(Textbook&) const;
                void deleteTextbook(Textbook&) const;
                void addChapter(Chapter&) const;
                void editChapter(Chapter&) const;
                void deleteChapter(Chapter&) const;
                void addSection(Section&) const;
                void editSection(Section&) const;
                void deleteSection(Section&) const;


                /* =====================================================================
                   Function  : cleanup
                   Purpose   : free memory in localstorage
                   Returns   : void
                ===================================================================== */
                void cleanup(); // Delete all the allocated data


        private:

                const StorageControl* const storageControl;
                User user;
                QList<Class*> classes;

};


#endif
