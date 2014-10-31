#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <QByteArray>
#include <QString>

#include "ConnectionServer.h"
#include "../../common/headers/Serializer.h"
#include "DBManager.h"
#include "../../common/headers/Definitions.h"

class Controller : public QObject {
    Q_OBJECT

  public:
    Controller(QObject *parent = 0);
    ~Controller();

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
    QCoreApplication *app;
    ConnectionServer *connection;
    Serializer *serializer;
    DBManager *dbManager;
};
#endif
