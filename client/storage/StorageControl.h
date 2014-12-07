#ifndef StorageControl_H
#define StorageControl_H

#include <QObject>
#include <QDebug>
#include <stdexcept>
#include "ClientSerializer.h"
#include "ConnectionClient.h"
#include "../../common/headers/Class.h"
#include "../../common/headers/Class.h"
#include "../../common/headers/Chapter.h"
#include "../../common/headers/Section.h"
#include "../../common/headers/Textbook.h"
#include "../../common/headers/Invoice.h"
#include "../../common/headers/User.h"

class StorageControl : public QObject {
        Q_OBJECT

    public:
        StorageControl(QString inIp = "127.0.0.1");

        ~StorageControl();

        void setIP(QString);

        void addTextbook(Class&) const;
        void editTextbook(Textbook&) const;
        void removeTextbook(Textbook&) const;

        void addChapter(Chapter&) const;
        void editChapter(Chapter&) const;
        void removeChapter(Chapter&) const;

        void addSection(Section&) const;
        void editSection(Section&) const;
        void removeSection(Section&) const;

        void addClass(Class&) const;
        void editClass(Class&);
        void removeClass(Class&);

        void removeCourse(Course&) const;

        void checkout(Invoice&) const;
        void refreshContent(User&, QList<Class*>&) const;

        void logIn(User&) const;


    private:
        ClientSerializer *serializer;
        ConnectionClient *connection;
        QString ip;

        void updateStorage(Serializable&, commands_t) const;


};

#endif // CONNECTIONCLIENT_H

