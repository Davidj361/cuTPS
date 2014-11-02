#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>

#include "headers/ConnectionClient.h"
#include "../common/headers/Textbook.h"
#include "../common/headers/Chapter.h"
#include "../common/headers/Section.h"
#include "../common/headers/Definitions.h"
#include "../common/headers/Serializer.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private slots:

    void runTests();
    void runTest1();
    void runTest2();
    void runTest3();

    void displayError(QString);

  private:

    Ui::MainWindow   *ui;
    ConnectionClient *connection;
    Serializer       *serializer;
    QString          *serverIP;

    QByteArray       res;
    QByteArray       req;

    int              portno;
};

#endif // MAINWINDOW_H
