#ifndef SERVERREQUESTCONTROL_H
#define SERVERREQUESTCONTROL_H

#include <QRunnable>
#include <QObject>
#include <QDebug>
#include <QByteArray>

#include "../databaseManagement/DBController.h"
#include "../../common/headers/Definitions.h"
#include "../../common/headers/User.h"
#include "../../common/headers/Student.h"
#include "ServerSerializer.h"

class ServerRequestControl :  public QObject, public QRunnable {
    Q_OBJECT
    public:

        ServerRequestControl(QByteArray *, DBController*);
        ~ServerRequestControl();

    signals:

        /* =========================================================================
        Function  : response
        Purpose   : Emit the signal that the work thread is finished
        Variables : OUT  -  QByteArray containing response to send to the client
        Returns   : void
        =========================================================================== */
        void response(QByteArray *out);

    protected:

        /* =========================================================================
        Function  : run
        Purpose   : Main function. This is where the work happens
        Returns   : void
        =========================================================================== */
        void run();

    private:

        QByteArray *in;
        DBController*const db;
};

#endif // SERVERREQUESTCONTROL_H
