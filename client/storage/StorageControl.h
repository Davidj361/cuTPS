#ifndef StorageControl_H
#define StorageControl_H

#include <QObject>
#include <QDebug>
#include <stdexcept>
#include "ClientSerializer.h"
#include "ConnectionClient.h"
#include "../../common/headers/Course.h"
#include "../../common/headers/Chapter.h"
#include "../../common/headers/Section.h"
#include "../../common/headers/Textbook.h"
#include "../../common/headers/Invoice.h"
#include "../../common/headers/User.h"



using namespace std;

class StorageControl : public QObject {
        Q_OBJECT

    public:
        StorageControl();

        ~StorageControl();

        void addTextbook(Textbook&);
        void editTextbook(Textbook&);
        void removeTextbook(Textbook&);
        void addChapter(Chapter&);
        void editChapter(Chapter&);
        void removeChapter(Chapter&);
        void addSection(Section&);
        void editSection(Section&);
        void removeSection(Section&);
        void addCourse(Course&);
        void editCourse(Course&);
        void removeCourse(Course&);
        void checkout(Invoice&);
        void refreshContent(User&, QList<Course*>&);
        User* logIn(User&);

    private:
        ClientSerializer *serializer;
        ConnectionClient *connection;
        QString ip;

        bool updateStorage(Serializable&, commands_t);


};

#endif // CONNECTIONCLIENT_H

