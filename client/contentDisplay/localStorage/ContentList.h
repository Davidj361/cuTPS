#ifndef GUARD_CONTENTLIST_H
#define GUARD_CONTENTLIST_H

#include <QList>

// Content list will hold all data with QList from the QT Library
// But it will have additional functionality that is needed by the system
class ContentList {
        public:
                // Should have const and non-const functions
                const User& getUser() const;
                const QList<Textbook*> getContentList() const;
                void update(User&, QList<Textbook*>, vector<Course*>);
        private:
                // We'll have a list of textbooks, and a list of chapters for the textbook, and a list of sections for the chapter
                QList<Textbook*> textbooks;
};

#endif
