#include "CourseManagement.h"

CourseManagement::CourseManagement(StorageControl &cStorage){
    storage = &cStorage;
}

void CourseManagement::addClass(QString courseCode, QString courseTitle, QString semester, int year){

    QString term(semester);
    term.append(" "+year);
    Course *course = new Course(courseCode, courseTitle);
    Class c(term,course);

    try{
        storage->addClass(c);
    } catch (runtime_error e){
        throw e;
    }
}

void CourseManagement::removeClass(QString courseCode, QString semester, int year){

    QString term(semester);
    term.append(" "+year);

    Course *course = new Course(courseCode, "");
    Class c(term,course);
    try{
        storage->removeClass(c);
    } catch (runtime_error e){
        throw e;
    }
}

void CourseManagement::removeCourse(QString courseCode){

    Course course(courseCode, "");
    try{
        storage->removeCourse(course);
    } catch (runtime_error e) {
        throw e;
    }
}
