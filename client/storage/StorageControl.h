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

        /* =====================================================================
           Function  : setip
           Purpose   : create a new connection with this ip
           Variables : In  -  the ip
           Returns   : void
          ===================================================================== */
        void setIP(QString);

        /* =====================================================================
           Functions : add edit remove
           Purpose   : update the server
           Variables : In  -  what is being changed
           Returns   : void
          ===================================================================== */
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
        void editClass(Class&) const;
        void removeClass(Class&) const;

        void removeCourse(Course&) const;

        void checkout(Invoice&) const;
        void refreshContent(User&, QList<Class*>&) const;

        /* =====================================================================
           Function  : logIn
           Purpose   : try to login as this user
           Variables : In  -  the user
           Returns   : void
          ===================================================================== */
        void logIn(User&) const;


    private:
        ClientSerializer *serializer;
        ConnectionClient *connection;
        QString ip;

        void updateStorage(Serializable&, commands_t) const;


};

#endif // CONNECTIONCLIENT_H

