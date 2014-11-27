#ifndef COURSE_H
#define COURSE_H
#include "Textbook.h"
#include "Serializable.h"
#include <QJsonObject>
#include <QJsonArray>
#include <vector>
#include <QString>
#include <QList>


using namespace std;

class Course : public Serializable{

    public:

        /* =====================================================================
        Function  : Course
        Purpose   : 
        Variables : 
        Returns   : 
        ===================================================================== */
        Course(QString, QString, QString);
        ~Course();

        QString getCourseTitle();
        QString getCourseCode();
        QString getTerm();
        QList<Textbook> getTextbooks();
        void addTextbook(Textbook);
        void removeTextbook(Textbook); 
        void serialize(QJsonObject&);

    private:
        QString courseTitle;
        QString courseCode;
        QString term;
        QList<Textbook> textbooks;

};

#endif // COURSE_H
