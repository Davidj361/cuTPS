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

        QString getCourseTitle();
        QString getCourseCode();
        void serialize(QJsonObject&);

    private:
        QString courseTitle;
        QString courseCode;
};

#endif // COURSE_H
