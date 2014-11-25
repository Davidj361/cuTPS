#ifndef StorageControl_H
#define StorageControl_H

#include <QObject>
#include <QDebug>
#include <stdexcept>
#include "ClientSerializer.h"
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
        void refreshContent(User&, QList<Textbook>&, QList<Course>&);


    private:
        ClientSerializer serializer;

};

#endif // CONNECTIONCLIENT_H

