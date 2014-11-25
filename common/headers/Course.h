#ifndef COURSE_H
#define COURSE_H
#include "Textbook.h"
#include <QJsonObject>
#include <vector>
#include <QString>
#include <QList>

using namespace std;

class Course {

    public:

        /* =====================================================================
        Function  : Course
        Purpose   : 
        Variables : 
        Returns   : 
        ===================================================================== */
        Course(QString, QString);
        ~Course();

        QString getCourseTitle();
        QString getCourseCode();
        QString getTerm();
        QList<Textbook> getTextbooks();
        void addTextbook(Textbook);
        void removeTextbook(Textbook); 

    private:
        QString courseTitle;
        QString courseCode;
        QString term;
        QList<Textbook> textbooks;

};

#endif // COURSE_H
