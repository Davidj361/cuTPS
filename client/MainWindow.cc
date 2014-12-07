#include "headers/MainWindow.h"
#include "ui_mainwindow.h"
#include "storage/StorageControl.h"
#include <QList>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow),
                                          refreshIcon("../resources/refresh.png"), refreshButton(refreshIcon, ""),
                                          localStorage(storageControl), checkout(storageControl, shoppingCart, localStorage) {
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
    //this->on_BtnLogin_clicked();



    ui->ipAddressTextbox->setText("127.0.0.1");

    portno = 60001;
    serverIP = new QString("127.0.0.1");

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

void MainWindow::popupError(const QString& error) {
        QMessageBox* message = new QMessageBox(QMessageBox::Critical, "Error", error);
        message->exec();
        delete message;
}
void MainWindow::refresh() {
        try {
                localStorage.refresh();
        } catch(runtime_error e) {
                this->popupError(e.what());
        }
        int currIndex = ui->stackedWidget->currentIndex();
        if (currIndex == ui->stackedWidget->indexOf(ui->MainStudent))
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

void MainWindow::studentSemesterListPopulate() {
    ui->courseList->clear();
    for (int i=0; i < localStorage.getClasses().size(); i++ ){
        Class* tempclass = localStorage.getClasses().at(i);
        ui->courseList->addItem(tempclass->getCourse()->getCourseCode());
    }
}
k
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
        storageControl.setIP(ui->ipAddressTextbox->text());
        localStorage.login(ui->UsernameBox->text(), ui->PasswordBox->text());
        ui->loginStatus->setText(localStorage.getUser().getUsername());
        this->displayMainStudent();
        this->refresh();
    } catch(runtime_error e) {
        ui->loginStatus->setText(e.what());
        qDebug() << e.what();
        //ui->loginStatus->setText("Invalid Username and Password");

    }
}

void MainWindow::on_BtnLogout_clicked()
{
    MainWindow::clearStudentCourseList();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->LoginPage));
}

// For when an item is selected in the semester list
void MainWindow::on_semesterList_itemPressed(QListWidgetItem *item)
{

}

// For when an item is selected in the course list
void MainWindow::on_courseList_itemPressed(QListWidgetItem *item)
{
    ui->contentList->clear();

    //Get the booklist
    QList<Textbook*> *studentContent = localStorage.getTextbooks(item->text());
    foreach (Textbook *t, *studentContent) {
        if (t->isAvailable()) {
            QListWidgetItem* textbookListItem = new QListWidgetItem(t->getTitle() + (t->isAvailable() ? "" : (" : $" + QVariant(t->getPrice()).toString() ) ) );
            if (t->isAvailable()) {
                    textbookListItem->setFlags(textbookListItem->flags() | Qt::ItemIsUserCheckable);
                    textbookListItem->setCheckState(Qt::Unchecked);
            } else {
                    textbookListItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            }
            ui->contentList->addItem(textbookListItem);
        }
        foreach (Chapter *ch, t->getChapters()) {
            if (ch->isAvailable()) {
                QListWidgetItem* chapterListItem = new QListWidgetItem("Ch." + QString::number(ch->getChapterNo()) + ": " + ch->getTitle() + (ch->isAvailable() ? "" : (" : $" + QVariant(ch->getPrice()).toString() ) ) );
                if (ch->isAvailable()) {
                        chapterListItem->setFlags(chapterListItem->flags() | Qt::ItemIsUserCheckable);
                        chapterListItem->setCheckState(Qt::Unchecked);
                } else {
                        chapterListItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                }
                ui->contentList->addItem(chapterListItem);
            }
            foreach (Section *s, ch->getSections()) {
                if (s->isAvailable()) {
                    QString spaces = "";
                    int length = QString("Ch.:" + QString::number(ch->getChapterNo())).length();
                    for (int i = 0; i < length; i++)
                            spaces += " ";
                    spaces += spaces;
                    QListWidgetItem* sectionListItem = new QListWidgetItem(spaces + s->getTitle() + (s->isAvailable() ? "" : (" : $" + QVariant(s->getPrice()).toString() ) ));
                    if (s->isAvailable()) {
                            sectionListItem->setFlags(sectionListItem->flags() | Qt::ItemIsUserCheckable);
                            sectionListItem->setCheckState(Qt::Unchecked);
                    } else {
                            sectionListItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                    }
                    ui->contentList->addItem(sectionListItem);
                }
            }
        }
    }

    //Sets item in contentList checkable
    /*
    QListWidgetItem* contentListItem = new QListWidgetItem(studentContent->at(0)->getTitle());
    contentListItem->setFlags(contentList->flags() | Qt::ItemIsUserCheckable);
    contentListItem->setCheckState(Qt::Unchecked);
    */


    //ui->contentList->addItem(contentListItem);
    //ui->contentList->addItem("Book1");
    //ui->contentList->addItem("Book2");
}

// DON'T USE THIS IF YOU WISH TO NOT HAVE CHECKBOXES FOR UNAVAILABLE ITEMS
void MainWindow::on_contentList_itemDoubleClicked(QListWidgetItem *item)
{
//    if (item->checkState() == Qt::Checked)
//        item->setCheckState(Qt::Unchecked);
//    else
//        item->setCheckState(Qt::Checked);
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




void MainWindow::on_contentList_itemClicked(QListWidgetItem *item)
{

    QList<Textbook*> *studentContent = localStorage.getTextbooks(ui->courseList->currentItem()->text());
    int count = 0;
    int index = ui->contentList->currentRow();
    foreach (Textbook *t, *studentContent) {
        if (count == index) {
            ui->courseDescription->setFontUnderline(true);
            ui->courseDescription->setText("Title");
            ui->courseDescription->setFontUnderline(false);
            ui->courseDescription->append(t->getTitle() + ": " + QString::number(t->getYear()));
            if (t->getEdition().length() > 0 ) {
                ui->courseDescription->setFontUnderline(true);
                ui->courseDescription->append("\nEdition");
                ui->courseDescription->setFontUnderline(false);
                ui->courseDescription->append(t->getEdition());
            }
            ui->courseDescription->setFontUnderline(true);
            ui->courseDescription->append("\nPublisher");
            ui->courseDescription->setFontUnderline(false);
            ui->courseDescription->append(t->getPublisher());
            ui->courseDescription->setFontUnderline(true);
            ui->courseDescription->append("\nAuthor");
            ui->courseDescription->setFontUnderline(false);
            ui->courseDescription->append(t->getAuthor());
            ui->courseDescription->setFontUnderline(true);
            ui->courseDescription->append("\nISBN");
            ui->courseDescription->setFontUnderline(false);
            ui->courseDescription->append(t->getISBN());
            if (t->isAvailable()) {
                ui->courseDescription->setFontUnderline(true);
                ui->courseDescription->append("\nPrice: ");
                ui->courseDescription->setFontUnderline(false);
                ui->courseDescription->append("$" + QString::number(t->getPrice()));
            }
            ui->courseDescription->setFontUnderline(true);
            ui->courseDescription->append("\nDescription");
            ui->courseDescription->setFontUnderline(false);
            ui->courseDescription->append("\n" + t->getDescription());
            count;
            break;
        }
        count++;
        foreach (Chapter *ch, t->getChapters()) {
            if (count == index) {
                ui->courseDescription->setFontUnderline(true);
                ui->courseDescription->setText("Chapter #");
                ui->courseDescription->setFontUnderline(false);
                ui->courseDescription->append(QString::number(ch->getChapterNo()));
                ui->courseDescription->setFontUnderline(true);
                ui->courseDescription->append("\nTitle");
                ui->courseDescription->setFontUnderline(false);
                ui->courseDescription->append(ch->getTitle());
                if (ch->isAvailable()) {
                    ui->courseDescription->setFontUnderline(true);
                    ui->courseDescription->append("\nPrice: ");
                    ui->courseDescription->setFontUnderline(false);
                    ui->courseDescription->append("$" + QString::number(ch->getPrice()));
                }
                ui->courseDescription->setFontUnderline(true);
                ui->courseDescription->append("\nDescription");
                ui->courseDescription->setFontUnderline(false);
                ui->courseDescription->append("\n" + ch->getDescription());
                count++;
                break;
            }
            count++;
            foreach (Section *s, ch->getSections()) {
                if (count == index) {
                    // ui->courseDescription->setText("Section: "+QString::number(s->getSectionNo()) + " " + s->getTitle() + " $" + QString::number(s->getPrice()));
                    // ui->courseDescription->append(s->getDescription());

                    ui->courseDescription->setFontUnderline(true);
                    ui->courseDescription->setText("Section #");
                    ui->courseDescription->setFontUnderline(false);
                    ui->courseDescription->append(QString::number(s->getSectionNo()));
                    ui->courseDescription->setFontUnderline(true);
                    ui->courseDescription->append("\nTitle");
                    ui->courseDescription->setFontUnderline(false);
                    ui->courseDescription->append(s->getTitle());
                    if (ch->isAvailable()) {
                            ui->courseDescription->setFontUnderline(true);
                            ui->courseDescription->append("\nPrice: ");
                            ui->courseDescription->setFontUnderline(false);
                            ui->courseDescription->append("$" + QString::number(s->getPrice()));
                    }
                    ui->courseDescription->setFontUnderline(true);
                    ui->courseDescription->append("\nDescription");
                    ui->courseDescription->setFontUnderline(false);
                    ui->courseDescription->append("\n" + s->getDescription());
                    count++;
                    break;
                }
                count++;
            }
        }
    }
}


void MainWindow::on_btnAddToCart_clicked()
{
    QList<int> selectedItems;
    ui->contentList->count();
    for (int i = 0; i < ui->contentList->count(); i ++) {
        if (ui->contentList->item(i)->checkState()) {
            selectedItems.push_back(i);
        }
    }
    if(selectedItems.count() == 0){
        return;
    }

    int count = 0;
    int index = -1;
    int ri = 0;

    if ( selectedItems.size() > ri ) {
        index = selectedItems.at(ri);
        ri++;
    }
    //qDebug() << "index is " + QString::number(index);

    QList<Textbook*> *studentContent = localStorage.getTextbooks(ui->courseList->currentItem()->text());
    foreach (Textbook *t, *studentContent) {
        if (count == index && index >= 0) {
            shoppingCart.addToCart(t);
            qDebug() << t->getTitle();
            if ( selectedItems.size() > ri ) {
                index = selectedItems.at(ri);
                ri++;
                qDebug() << QString::number(index);
            }
            else
                index = -1;
        }
        count++;
        foreach (Chapter *ch, t->getChapters()) {
            qDebug() << " Index " << QString::number(index)<<" count "<< QString::number(count);
            if (count == index && index >= 0) {
                qDebug() << ch->getTitle();
                shoppingCart.addToCart(ch);
                if ( selectedItems.size() > ri ) {
                    index = selectedItems.at(ri);
                    ri++;
                    qDebug() << QString::number(index);
                }
                else
                    index = -1;
            }
            count++;
            foreach (Section *s, ch->getSections()) {
                if (count == index && index >= 0) {
                    shoppingCart.addToCart(s);
                    qDebug() << s->getTitle();

                    if ( selectedItems.size() > ri ) {
                        index = selectedItems.at(ri);
                        ri++;
                        qDebug() << QString::number(index);
                    }
                    else
                        index = -1;
                }
                count++;
            }
        }
    }
    qDebug() << QString::number(shoppingCart.getCartContents().size()) + " added to the Cart";

}

void MainWindow::on_btnViewCart_clicked()
{

    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->ShoppingCartStudent));
    QList<Content*> content = shoppingCart.getCartContents();
    foreach(Content * c, content){
        QListWidgetItem* contentListItem = new QListWidgetItem(c->getTitle()+" $"+QString::number(c->getPrice()));
        ui->listWidgetShoppingCart->addItem(contentListItem);
    }

}



void MainWindow::on_btnClearCart_clicked()
{
    shoppingCart.clearCart();
    while (ui->listWidgetShoppingCart->count() > 0) {
        ui->listWidgetShoppingCart->takeItem(0);
    }
}

void MainWindow::on_btnPreviousPage_clicked()
{
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->MainStudent));
}

void MainWindow::on_btnCheckout_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->ShoppingCartGatherCreditCardInfo));
    //TODO delete the following lines after it works
    ui->lineName->setText("h");
    ui->lineEmail->setText("h");
    ui->linedate->setText("h");
    ui->lineCC->setText("h");
    ui->lineCvv->setText("h");

}

void MainWindow::on_btnProcedeCheckout_clicked()
{
    // If none of the fields are empty
    QList<QLineEdit*> fieldList;
    fieldList.append(ui->lineName);
    fieldList.append(ui->lineEmail);
    fieldList.append(ui->linedate);
    fieldList.append(ui->lineCvv);
    fieldList.append(ui->lineCC);
    foreach(QLineEdit *e, fieldList) {
        if (e->text().compare("") == 0) {
            ui->billingInfoError->setText("One of your fields is empty or invalid");
            return;
        }
    }
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->ShoppingCartOrderConfirmed));
    try{
        checkout.checkout();
    } catch(runtime_error e){
        this->popupError(e.what());
        ui->billingInfoError->setText(e.what());
    }

    foreach(QLineEdit *e, fieldList) {
        e->setText("");
    }
    this->on_btnClearCart_clicked();

}

void MainWindow::on_btnConfirmationMainPage_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->MainStudent));
}

void MainWindow::on_btnConfirmationLogout_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->LoginPage));
}
