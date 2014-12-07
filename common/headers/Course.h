#ifndef COURSE_H
#define COURSE_H

#include "Textbook.h"
#include "Serializable.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QList>


using namespace std;

class Course : public Serializable{

    public:

        Course(QString courseCode, QString courseTitle);
        ~Course();

        const QString& getCourseTitle() const;
        QString getCourseCode();
        QString getNewCourseCode();
        void setNewCourseCode(QString);
        void serialize(QJsonObject&) const;

    private:
        QString courseTitle;
        QString courseCode;
        QString updatedCourseCode;
};

#endif // COURSE_H
