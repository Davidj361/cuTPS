#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QScrollBar>
#include <QListWidgetItem>
#include <QPushButton>
#include <QIcon>
#include <QMessageBox>
#include <exception>

#include "storage/ConnectionClient.h"
#include "storage/StorageControl.h"
#include "purchase/shoppingCartManagement/shoppingCart.h"
#include "../common/headers/Textbook.h"
#include "../common/headers/Chapter.h"
#include "../common/headers/Section.h"
#include "../common/headers/Definitions.h"
#include "contentDisplay/localStorage/localStorage.h"
#include "../purchase/checkout/checkout.h"

namespace Ui {
        class MainWindow;
}

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);

        ~MainWindow();

    private slots:

        void clearList();
        void setServerIP();
        
        void studentSemesterListPopulate();
        void courseManagerSemesterListPopulate();

        void clearStudentCourseList();

        void scrollDown();
        
        void popupWarning(const QString&);

        void popupError(const QString&);

        void refresh();

        void displayError(QString);


        void on_BtnClear_clicked();

        void on_BtnLogin_clicked();

        void on_courseManagerAddButton_released();

        void on_courseManagerDeleteButton_released();

        void on_courseManagerSemesterList_itemPressed(QListWidgetItem *item);

        void on_courseManagerCourseList_itemPressed(QListWidgetItem *item);
        
        void on_semesterList_itemPressed(QListWidgetItem *item);

        void on_courseList_itemPressed(QListWidgetItem *item);

        bool validUsernamePassword();

        bool isStudent();

        void on_contentList_itemClicked(QListWidgetItem *item);


        void displayMainStudent();

        void displayCourseManager();


        void on_btnAddToCart_clicked();

        void on_btnViewCart_clicked();


        void on_btnClearCart_clicked();

        void on_btnPreviousPage_clicked();

        void on_btnCheckout_clicked();

        void on_btnProcedeCheckout_clicked();

        void on_btnConfirmationMainPage_clicked();

        void courseManagerClearLists();

        void update_Shopping_Cart_Count();

        void clear_All_Widgets();

        void on_actionQuit_triggered();

        void on_actionLogout_triggered();

private:

        Ui::MainWindow    *ui;
        QString           *serverIP;
        QIcon refreshIcon;
        QPushButton refreshButton;

        QString anISBN;
        int     aChapterNumber;
        int     aSectionNumber;

        QByteArray       res;
        QByteArray       req;

        int              portno;

        // Subsystems
        ShoppingCart shoppingCart;
        StorageControl storageControl;
        LocalStorage   localStorage;
        Checkout checkout;
};

#endif // MAINWINDOW_H
