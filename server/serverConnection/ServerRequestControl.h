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
        void response(QByteArray *out);

    protected:

        void run();

    private:
        QByteArray *in;
        DBController *db;
};

#endif // SERVERREQUESTCONTROL_H
