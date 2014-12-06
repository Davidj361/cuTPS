#include "headers/MainWindow.h"
#include "ui_mainwindow.h"
#include "storage/StorageControl.h"
#include <QList>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow),
                                          refreshIcon("../resources/refresh.png"), refreshButton(refreshIcon, ""),
                                          localStorage(storageControl) {
    ui->setupUi(this);

    /*  Set Background Image  */
    /*
    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap("images/red.jpg")))));
    setPalette(*palette);
    */

    ui->UsernameBox->setText("bruce");
    ui->PasswordBox->setText("password");

    ui->UsernameBox->setFocus();

    // Add a clickable icon to the status bar to it's far right
    ui->statusBar->addPermanentWidget(&refreshButton);



    serverIP = new QString("127.0.0.1");
    portno = 60001;

    connection = new ConnectionClient(serverIP, portno);
    // storageControl = new StorageControl(); // no longer pointer
    serializer = new Serializer();


    book_list = 0;

    anISBN = "1232467890";
    aChapterNumber = 1;
    aSectionNumber = 1;


    connect(ui->actionQuit,     SIGNAL(triggered()), this, SLOT(close()));

    connect(ui->runTestsButton, SIGNAL(clicked()),   this, SLOT(runTests()));
    connect(ui->btnRunTest1,    SIGNAL(clicked()),   this, SLOT(addContentTest()));
    connect(ui->btnRunTest2,    SIGNAL(clicked()),   this, SLOT(getContentTest()));
    connect(ui->btnRunTest3,    SIGNAL(clicked()),   this, SLOT(addInvoiceTest()));
    connect(ui->btnClear,       SIGNAL(clicked()),   this, SLOT(clearList()));
    connect(ui->btnSetIP,       SIGNAL(clicked()),   this, SLOT(setServerIP()));



    ui->btnRunTest3->setEnabled(false);


    // For autscrolling to the bottom of the list
    connect(ui->resultsListWidget->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT(scrollDown()));

    // For when the user clicks the refresh button
    connect(&refreshButton, SIGNAL(clicked(bool)), this, SLOT(refresh()));

    connect(connection, SIGNAL(ConnectionError(QString)), this, SLOT(displayError(QString)));
}

MainWindow::~MainWindow() {
    for (int i = 0; i < ui->resultsListWidget->count(); i++)
        delete ui->resultsListWidget->item(i);
    delete ui;
    delete connection;
    delete serverIP;
    delete serializer;
    freeBookList();
    delete book_list;
    // delete storageControl; // No longer a pointer
}

void MainWindow::scrollDown() {
    ui->resultsListWidget->scrollToBottom();
}

void MainWindow::refresh() {
        localStorage.refresh();
        // TODO Make it perform the right UI populate depending on which panel is focused
        this->studentCourseListPopulate();
}

void MainWindow::clearList() {
    ui->resultsListWidget->clear();
}

void MainWindow::setServerIP() {
    *serverIP = ui->txtServerIP->text();
    ui->statusBar->showMessage("Server IP address set");
}

void MainWindow::freeBookList() {
    if (book_list == 0)
        return;
    for (vector<Textbook *>::iterator it = book_list->begin(); it != book_list->end(); ++it) {
        if (*it != 0) {
            delete *it;
            *it = 0;
        }
    }
    delete book_list;
    book_list = 0;
}

/*
void MainWindow::runTests() {
    addContentTest();
    getContentTest();
    addInvoiceTest();
}

void *MainWindow::runTest(QListWidgetItem *listItem, commands_t in_command, void *in_object, QString message) {

    QString result;
    QString errorMsg;
    void *object = 0;

    res.clear();
    req.clear();

    try {
        listItem->setText(message);
        qDebug() << "Serializing Request...";
        serializer->Serialize(in_command, in_object, REQUEST, req);
        qDebug() << "Serialized request is:";
        qDebug() << req;
        qDebug() << "Sending request to server...";
        connection->request(req, res);
        qDebug() << "Response from server size is: " << res.size();
        qDebug() << "Deserializing request...";
        serializer->Deserialize(res, object, result, errorMsg);
        qDebug() << "Deserializing done. Displaying results to GUI";
        listItem->setText(message + " " + result);
        if (result == "error")
            listItem->setText(listItem->text() + "\n " + errorMsg);
        listItem->setForeground( (result == "success") ? QBrush(Qt::green) : QBrush(Qt::red) );
    }
    catch (exception &e) {
        qDebug() << "Exception!";
        qDebug() << e.what();
        listItem->setText(message + "\n  Exception! " + e.what());
        listItem->setForeground(QBrush(Qt::red));
    }
    return object;
}

// Add Content test NOT NEEDED
void MainWindow::addContentTest() {

    qDebug() << "Running test 1 - Adding Content";

    ui->btnRunTest1->setEnabled(false);

    QListWidgetItem *test1 = new QListWidgetItem; // Add textbook test
    QListWidgetItem *test2 = new QListWidgetItem; // Add chapter test
    QListWidgetItem *test3 = new QListWidgetItem; // Add section test
    QListWidgetItem *test4 = new QListWidgetItem; // Add textbook test
    QListWidgetItem *test5 = new QListWidgetItem; // Add chapter test
    QListWidgetItem *test6 = new QListWidgetItem; // Add section test

    ui->resultsListWidget->addItem(test1);
    ui->resultsListWidget->addItem(test2);
    ui->resultsListWidget->addItem(test3);
    ui->resultsListWidget->addItem(test4);
    ui->resultsListWidget->addItem(test5);
    ui->resultsListWidget->addItem(test6);



    Textbook t(anISBN, "Learning NodeJS", "David J", "Graeme J", 2014, "1", "Everything you need to know about NodeJS", true, 50);
    Chapter  c("V8 Engine", aChapterNumber, &t, "More horsepower!", true, 15);
    Section  s("Many ponies", aSectionNumber, &c, &t, "Ponies are funny looking", true, 5);


    runTest(test1, ADD_TEXTBOOK, &t, "Attempting to add a textbook with isbn " + anISBN);
    runTest(test2, ADD_CHAPTER, &c, "Attempting to add chapter number " + QString::number(aChapterNumber) + " of " + anISBN);
    runTest(test3, ADD_SECTION, &s, "Attempting to add section number " + QString::number(aSectionNumber) + " of chapter " + QString::number(aChapterNumber) + " of " + anISBN);

    runTest(test4, ADD_TEXTBOOK, &t, "Attempting to add a textbook with isbn " + anISBN);
    runTest(test5, ADD_CHAPTER, &c, "Attempting to add chapter number " + QString::number(aChapterNumber) + " of " + anISBN);
    runTest(test6, ADD_SECTION, &s, "Attempting to add section number " + QString::number(aSectionNumber) + " of chapter " + QString::number(aChapterNumber) + " of " + anISBN);

    anISBN = QString::number(anISBN.toInt() + 1);
    ++aChapterNumber;
    ++aSectionNumber;

    ui->btnRunTest1->setEnabled(true);
}


void MainWindow::getContentTest() {
    getContentStudentTest();
    getContentCMTest();
}

void MainWindow::getContentStudentTest() {

    ui->btnRunTest2->setEnabled(false);

    QListWidgetItem *test1 = new QListWidgetItem; // Retrieve content

    ui->resultsListWidget->addItem(test1);

    freeBookList();
    // book_list = static_cast<vector<Textbook *>*>(runTest(test1, GET_CONTENT, userStu, "Performing Retrieve Content test for a Student..."));

    ui->btnRunTest3->setEnabled(true);

    ui->btnRunTest2->setEnabled(true);
}

void MainWindow::getContentCMTest() {

    ui->btnRunTest2->setEnabled(false);

    QListWidgetItem *test1 = new QListWidgetItem; // Retrieve content

    ui->resultsListWidget->addItem(test1);

    freeBookList();
    // book_list = static_cast<vector<Textbook *>*>(runTest(test1, GET_CONTENT, userCM, "Performing Retrieve Content test for a Content Manager..."));

    ui->btnRunTest3->setEnabled(true);

    ui->btnRunTest2->setEnabled(true);
}

void MainWindow::addInvoiceTest() {
    qDebug() << "Running test 3 - Adding Invoice";

    ui->btnRunTest3->setEnabled(false);

    QListWidgetItem *test1 = new QListWidgetItem; // Retrieve content

    ui->resultsListWidget->addItem(test1);

    // Invoice invoice (userStu->getUsername());

    Textbook *t = book_list->front();

    invoice.addContent(t);

    runTest(test1, ADD_INVOICE, &invoice, "Performing Add Invoice test...");

    ui->btnRunTest3->setEnabled(true);
}
*/

void MainWindow::displayError(QString error) {
    ui->statusBar->showMessage(error);
}

void MainWindow::studentCourseListPopulate() {
    /*
    for (int i = 0; i < studentCourseList->size(); i++ )
        ui->courseList->addItem(studentCourseList->at(0));

    ui->courseList->addItem("COMP1001");
    ui->courseList->addItem("PSYCH2002");
    ui->courseList->addItem("POLI3003");
    */
    // on_courseList_itemPressed
    ui->courseList->clear();
    for (int i=0; i < localStorage.getClasses().size(); i++ ){
        Class* tempclass = localStorage.getClasses().at(i);
        ui->courseList->addItem(tempclass->getCourse()->getCourseCode());
    }
}

void MainWindow::clearStudentCourseList() {

    while (ui->courseList->count() > 0) {
        ui->courseList->takeItem(0);
        }
}


void MainWindow::on_BtnClear_clicked()
{
    ui->UsernameBox->clear();
    ui->PasswordBox->clear();
    ui->loginStatus->setText("");
}

void MainWindow::on_BtnLogin_clicked()
{
    //user = storageControl->logIn(User(ui->UsernameBox->text(), ui->PasswordBox->text(),"",""));
    // user = User(ui->UsernameBox->text(), ui->PasswordBox->text(),"","");
    try {
        localStorage.login(ui->UsernameBox->text(), ui->PasswordBox->text());
        ui->loginStatus->setText(localStorage.getUser().getUsername());
        this->refresh();
        this->displayMainStudent();
    } catch(runtime_error e) {
        ui->loginStatus->setText(e.what());
        qDebug() << e.what();
        //ui->loginStatus->setText("Invalid Username and Password");

    }
    /*
    if (ui->UsernameBox->text() == "student") {
        MainWindow::studentClassListPopulate();
        ui->courseDescription->setReadOnly(true); // set counrse Description textbox to read-only
    }

    if (ui->UsernameBox->text() == "cm") {
    }
    */
    /*
    if (MainWindow::validUsernamePassword() && MainWindow::isStudent()) {
        MainWindow::studentCourseListPopulate();
        ui->courseDescription->setReadOnly(true); // set counrse Description textbox to read-only
    } else {
        //ui->loginStatus->setText(ui->UsernameBox->text());
        ui->loginStatus->setText(storageControl->logIn(*user)->getUsername());
    }
    */
}

void MainWindow::on_BtnLogout_clicked()
{
    MainWindow::clearStudentCourseList();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->LoginPage));
}

// For when an item is selected in the course list
void MainWindow::on_courseList_itemPressed(QListWidgetItem *item)
{
    while (ui->contentList->count() > 0) {
        ui->contentList->takeItem(0);
    }
    QListWidgetItem* course1 = new QListWidgetItem(item->text());
    course1->setFlags(course1->flags() | Qt::ItemIsUserCheckable);
    course1->setCheckState(Qt::Unchecked);

    ui->courseDescription->setText(item->text());
    ui->contentList->addItem(course1);
}

void MainWindow::on_contentList_itemDoubleClicked(QListWidgetItem *item)
{
    if (item->checkState() == Qt::Checked)
        item->setCheckState(Qt::Unchecked);
    else
        item->setCheckState(Qt::Checked);
}

bool MainWindow::validUsernamePassword() {
    return true;
}

bool MainWindow::isStudent() {
    return true;
}

void MainWindow::displayMainStudent() {
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->MainStudent));
}

void MainWindow::on_semesterList_itemPressed(QListWidgetItem *item)
{

}
