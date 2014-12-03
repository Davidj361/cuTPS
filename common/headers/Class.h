#ifndef CLASS_H
#define CLASS_H

#include "Course.h"
#include "Textbook.h"
#include "Student.h"
#include "Serializable.h"

#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>

using namespace std;

class Class : public Serializable {

    public:

        Class (QString semester, Course *course);
        ~Class();

        QString getSemester();
        Course* getCourse();
        QList<Textbook*> getBooklist();
        QList<Student *> getClasslist();
        void addTextbook(Textbook *);
        void addStudent(Student *);
        void serialize(QJsonObject &);

    private:

        QString semester;
        Course *course;
        QList<Textbook *> booklist;
        QList<Student *> classlist;
};

#endif // CLASS_H
