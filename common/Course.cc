#include "headers/Course.h"

Course::Course(QString courseCode, QString courseTitle){

    this->courseCode = courseCode;
    this->courseTitle = courseTitle;

}
void Course::serialize(QJsonObject &json) const {
    json.insert("courseCode", courseCode);
    json.insert("courseTitle", courseTitle);

}

Course::~Course() {
}

const QString& Course::getCourseTitle() const {
    return courseTitle;
}

QString Course::getCourseCode(){
    return courseCode;
}

QString Course::getNewCourseCode() {
    return updatedCourseCode;
}

void Course::setNewCourseCode(QString newCode) {
    this->updatedCourseCode = newCode;
}
