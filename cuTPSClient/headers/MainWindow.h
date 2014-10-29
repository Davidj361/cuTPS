#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>


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
        QString *serverIP;
        int    portno;
};

#endif // MAINWINDOW_H
