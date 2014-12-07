#include "headers/Class.h"


Class::Class(): course(0) {}

// FIXME Make this copy properly
Class::Class(const Class& ass) : semester(ass.semester), course(ass.course), booklist(ass.booklist), classlist(ass.classlist) {}

Class::Class(QString semester, Course *course) {
    this->semester = semester;
    this->course = course;
}

Class::~Class() {
    Textbook *t;
    foreach (t, booklist) {
        delete t;
        t = 0;
    }
    Student *s;
    foreach (s, classlist) {
        delete s;
        s = 0;
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

QList<Student *> &Class::getClasslist() {
    return classlist;
}

void Class::addStudent(Student *student) {
    classlist.append(student);
}

void Class::addTextbook(Textbook *textbook) {
    booklist.append(textbook);
}
