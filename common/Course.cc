#include "headers/Course.h"

Course::Course(QString courseCode, QString courseTitle){
    this->courseCode = courseCode;
    this->courseTitle = courseTitle;
    // This field for EDIT_TEXTBOOK only!
    this->updatedCourseCode = "";
}
void Course::serialize(QJsonObject &json){
    json.insert("courseCode", courseCode);
    json.insert("courseTitle", courseTitle);
    if (!updatedCourseCode.isEmpty())
        json.insert("newCourseCode", updatedCourseCode);
}

Course::~Course() {
}

QString Course::getCourseTitle(){
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
