#ifndef COURSEMANAGEMENT_H
#define COURSEMANAGEMENT_H
#include "../../common/headers/Course.h"
#include "../../common/headers/Class.h"
#include "../storage/StorageControl.h"

class CourseManagement{
    public:

        CourseManagement(StorageControl&);

        /* =====================================================================
           Function  : addClass;
           Purpose   : create a class
           Returns   : void
        ===================================================================== */
        void addClass(QString courseCode, QString courseTitle, QString semester, int year);

        /* =====================================================================
           Function  : removeClass;
           Purpose   : removes a class
           Variables : minimal variables required to delete class
           Returns   : void
        ===================================================================== */
        void removeClass(QString courseCode, QString semester, int year);

        /* =====================================================================
           Function  : removeCourse;
           Purpose   : removes a course
           Variables : minimal variables required to delete course
           Returns   : void
        ===================================================================== */
        void removeCourse(QString courseCode);

    private:
        StorageControl* storage;



};

#endif
