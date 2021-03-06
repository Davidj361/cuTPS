#include "headers/Class.h"


Class::Class(): course(0) {}

// This is needed for UI stuff
Class::Class(const Class& ass) : semester(ass.semester), course(0) {}

Class::Class(QString semester, const Course& course) : semester(semester) {
        this->course = new Course(course);
}

Class::Class(QString semester, Course *course) {
    this->semester = semester;
    this->course = course;
}

Class::~Class() {
    foreach (Textbook* t, booklist) {
        if (t != 0) {
            delete t;
            t = 0;
        }
    }
    if (course != 0)
        delete course;
    }

void Class::serialize(QJsonObject &json) const {
    json.insert("semester", semester);
    QJsonObject jcourse;
    course->serialize(jcourse);
    json.insert("course", jcourse);

    QJsonArray tbs;
    foreach(Textbook *t, booklist){
        QJsonObject tjson;
        t->serialize(tjson);
        tbs.append(tjson);
    }
    json["booklist"] = tbs;
}

const QString Class::getSemester() const {
    return semester;
}

Course* Class::getCourse() const {
    return course;
}

QList<Textbook *> &Class::getBooklist() {
    return booklist;
}

void Class::addTextbook(Textbook *textbook) {
    booklist.append(textbook);
}
