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

        void addClass(Class&);
        void editClass(Class&);
        void removeClass(Class&);
        void checkout(Invoice&) const;
        void refreshContent(User&, QList<Class*>&);

        void logIn(User&);

    private:
        ClientSerializer *serializer;
        ConnectionClient *connection;
        QString ip;

        bool updateStorage(Serializable&, commands_t) const;


};

#endif // CONNECTIONCLIENT_H

