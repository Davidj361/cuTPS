#ifndef SERVERREQUESTCONTROL_H
#define SERVERREQUESTCONTROL_H

#include <QRunnable>
#include <QObject>
#include <QDebug>
#include <QByteArray>

#include "ConnectionServer.h"
#include "../databaseManagement/DBController.h"
#include "../../common/headers/Definitions.h"
#include "../../common/headers/User.h"
#include "../../common/headers/Student.h"
#include "ServerSerializer.h"

class ServerRequestControl :  public QObject, public QRunnable {
    Q_OBJECT
    public:
        ServerRequestControl(QByteArray *);
        ~ServerRequestControl();

    signals:
        void response(QByteArray *out);

    protected:

        void run();

    private:
        QByteArray *in;
};

#endif // SERVERREQUESTCONTROL_H
