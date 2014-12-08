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
                Class(const Class&);

                Class(QString semester, Course *course);
                // For LocalStorage to easily create new objects and not deal with memory
                Class(QString semester, const Course& course);
                ~Class();

                const QString getSemester() const;
                Course* getCourse() const;
                QList<Textbook*> &getBooklist();
                void addTextbook(Textbook *);
                void serialize(QJsonObject &) const;

        private:

                QString semester;
                Course *course;
                QList<Textbook *> booklist;
};

// Need this for setData()
Q_DECLARE_METATYPE(Class)
Q_DECLARE_METATYPE(Class*)

#endif // CLASS_H
