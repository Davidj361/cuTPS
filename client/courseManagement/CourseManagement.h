#ifndef COURSEMANAGEMENT_H
#define COURSEMANAGEMENT_H
#include "../../common/headers/Course.h"
#include "../../common/headers/Class.h"
#include "../storage/StorageControl.h"

class CourseManagement{
    public:
        CourseManagement(StorageControl&);

        void addClass(QString, QString, QString, int);
        void removeClass(QString courseCode, QString courseTitle, QString semester, int year);

    private:
        StorageControl* storage;



};

#endif
