#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Student: public User {

    public:

        /* =====================================================================
        Function  : Section
        Purpose   : Constructs an Section object
        Variables : IN  -  Username
                        -  Password
                        -  Name
        Returns   : void
        ===================================================================== */

        Student(QString, QString, QString);

};

#endif // STUDENT_H
