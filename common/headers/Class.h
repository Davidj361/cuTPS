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
#include <QMetaType>

class Class : public Serializable {

        public:
                // Need this for setData()
                Class();
                // FIXME Make this copy properly
                Class(const Class&);

                Class(QString semester, Course *course);
                ~Class();

                const QString getSemester() const;
                Course* getCourse() const;
                QList<Textbook*> &getBooklist();
                QList<Student *> &getClasslist();
                void addTextbook(Textbook *);
                void addStudent(Student *);
                void serialize(QJsonObject &) const;

        private:

                QString semester;
                Course *course;
                QList<Textbook *> booklist;
                QList<Student *> classlist;
};

// Need this for setData()
Q_DECLARE_METATYPE(Class)
Q_DECLARE_OPAQUE_POINTER(Class*)

#endif // CLASS_H
