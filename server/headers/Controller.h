#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QCoreApplication>

class Controller : public QObject {
    Q_OBJECT

    public:
        Controller(QObject *parent = 0);
        ~Controller();

        /* =====================================================================
        Function  : Run
        Purpose   : The main loop of the server process
        Variables : None
        Returns   : 1 - Success
                    0 - Fail
        ===================================================================== */
        int Run();

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
        Function  : AboutToQuitApp
        Purpose   : Slot for when application is about to quit
        Variables : None
        Returns   : void
        ===================================================================== */
        void AboutToQuitApp();

    private:
        // Reference to the main application instance
        QCoreApplication *app;
};
#endif
