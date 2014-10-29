#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>

#include "headers/ConnectionClient.h"
#include "../common/headers/Definitions.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
    void runTests();
    void runTest1();
    void runTest2();
    void runTest3();


    private:
        Ui::MainWindow *ui;
        ConnectionClient *connection;
        QString *serverIP;
        int    portno;
};

#endif // MAINWINDOW_H
