#ifndef SERVERCONNECTIONCONTROLLER_H
#define SERVERCONNECTIONCONTROLLER_H

#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <QByteArray>
#include <QJsonObject>
#include <QString>

#include "ConnectionServer.h"
#include "../databaseManagement/DBController.h"
#include "../../common/headers/Definitions.h"
#include "../../common/headers/User.h"
#include "../../common/headers/Student.h"
#include "ServerSerializer.h"

class ServerConnectionController : public QObject {
        Q_OBJECT

    public:
        ServerConnectionController(QObject *parent = 0);
        ~ServerConnectionController();
        void doTask(QByteArray& in);
        /* =====================================================================
        Function  : Quit
        Purpose   : Tells the main application to quit
        Variables : None
        Returns   : void
        ===================================================================== */
        void Quit();

    signals:
        /* =====================================================================
        Function  : Finished
        Purpose   : Signal telling to finished();
        Variables : None
        Returns   : void
        ===================================================================== */
        void Finished();

    public slots:
        /* =====================================================================
        Function  : Run
        Purpose   : The main loop of the server process
        Variables : None
        Returns   : void
        ===================================================================== */
        void Run();

        /* =====================================================================
        Function  : AboutToQuitApp
        Purpose   : Slot for when application is about to quit
        Variables : None
        Returns   : void
        ===================================================================== */
        void AboutToQuitApp();

    private:

        // Adding a cleanup function for the void* object depending on command type
        int cleanup(commands_t, void *&);

        QCoreApplication *app;
        ConnectionServer *connection;
        ServerSerializer *serializer;
        DBController *db;

};
#endif
