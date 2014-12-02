#ifndef StorageControl_H
#define StorageControl_H

#include <QObject>
#include <QDebug>
#include <stdexcept>
#include "ClientSerializer.h"
#include "ConnectionClient.h"
#include "../../common/headers/Course.h"
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
        void addCourse(Course&);
        void editCourse(Course&);
        void removeCourse(Course&);
        void checkout(Invoice&);
        void refreshContent(User&, QList<Course*>&);

    private:
        ClientSerializer *serializer;
        ConnectionClient *connection;

        bool updateStorage(Serializable&, commands_t);


};

#endif // CONNECTIONCLIENT_H

