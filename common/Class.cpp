#include "headers/Class.h"

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
    // Todo - Delete me if the above works
    //    for (QList<Textbook*>::iterator iter = this->textbooks.begin(); iter != this->textbooks.end(); ++iter) {
    //        delete *iter;
    //        *iter = 0;
    //    }
}

void Class::serialize(QJsonObject &json) {
    json.insert("semester", semester);
    json.insert("courseCode", course->getCourseCode());
    json.insert("courseTitle", course->getCourseTitle());
    QJsonObject jcourse;
    course->serialize(jcourse);
    json.insert("course", jcourse)
}

QString Class::getSemester() {
    return semester;
}

Course* Class::getCourse() {
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
