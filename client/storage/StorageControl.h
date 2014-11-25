#ifndef StorageControl_H
#define StorageControl_H

#include <QObject>
#include <QDebug>
#include <stdexcept>


using namespace std;

class StorageControl : public QObject {
        Q_OBJECT

    public:
        StorageControl();

        ~StorageControl();

        void addTextbook(Textbook);
	void editTextbook(Textbook);
        void removeTextbook(Textbook);
        void addCourse(Course);
        void editCourse(Course);
        void removeCourse(Course);
        void checkout(Invoice);
        void refreshContent(User, QList<Textbook>, QList<Course>);


    private:

};

#endif // CONNECTIONCLIENT_H

