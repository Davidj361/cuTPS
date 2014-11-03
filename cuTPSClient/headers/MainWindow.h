#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QScrollBar>
#include <QListWidgetItem>

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
    void addContentTest();
    void getContentTest();
    void addInvoiceTest();

    void scrollDown();

    void displayError(QString);

  private:

    Ui::MainWindow    *ui;
    ConnectionClient  *connection;
    Serializer        *serializer;
    QString           *serverIP;
    User              *userStu;
    User              *userCM;
    vector<Textbook*> *book_list;

    QByteArray       res;
    QByteArray       req;

    int              portno;

    void * runTest(QListWidgetItem*, commands_t, void*, QString);
    void getContentStudentTest();
    void getContentCMTest();
};

#endif // MAINWINDOW_H
