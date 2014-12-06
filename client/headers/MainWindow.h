#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QScrollBar>
#include <QListWidgetItem>
#include <QPushButton>
#include <QIcon>
#include <exception>

#include "storage/ConnectionClient.h"
#include "storage/StorageControl.h"
#include "../common/headers/Textbook.h"
#include "../common/headers/Chapter.h"
#include "../common/headers/Section.h"
#include "../common/headers/Definitions.h"
#include "../common/headers/Serializer.h"
#include "contentDisplay/localStorage/localStorage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);

        ~MainWindow();

    private slots:

            /*
        void runTests();
        void addContentTest();
        void getContentTest();
        void addInvoiceTest();
        */
        void clearList();
        void setServerIP();
        void studentCourseListPopulate();

        void clearStudentCourseList();

        void scrollDown();
        
        void refresh();

        void displayError(QString);


        void on_BtnClear_clicked();

        void on_BtnLogin_clicked();

        void on_BtnLogout_clicked();

        void on_semesterList_itemPressed(QListWidgetItem *item);

        void on_courseList_itemPressed(QListWidgetItem *item);

        void on_contentList_itemDoubleClicked(QListWidgetItem *item);

        bool validUsernamePassword();

        bool isStudent();

        void displayMainStudent();

        void on_contentList_itemClicked(QListWidgetItem *item);


private:

        Ui::MainWindow    *ui;
        ConnectionClient  *connection;
        Serializer        *serializer;
        QString           *serverIP;
        // User              *user;
        // User              *userStu;
        // User              *userCM;
        vector<Textbook *> *book_list;
        QIcon refreshIcon;
        QPushButton refreshButton;

        QString anISBN;
        int     aChapterNumber;
        int     aSectionNumber;

        QByteArray       res;
        QByteArray       req;

        int              portno;

        void *runTest(QListWidgetItem *, commands_t, void *, QString);
        void getContentStudentTest();
        void getContentCMTest();
        void freeBookList();
        
        // Subsystems
        StorageControl storageControl; // TODO make non-pointer
        LocalStorage   localStorage;
};

#endif // MAINWINDOW_H
