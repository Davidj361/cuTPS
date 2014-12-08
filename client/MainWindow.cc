#include "headers/MainWindow.h"
#include "ui_mainwindow.h"
#include "storage/StorageControl.h"
#include <QList>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow),
                                          refreshIcon("../resources/refresh.png"), refreshButton(refreshIcon, ""),
                                          localStorage(storageControl), checkout(storageControl, shoppingCart, localStorage) {
    ui->setupUi(this);
    // Needed for ui/ContentManager.h
    ui->contentManagerPage->setUi(ui);

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

    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->loginPage));

    ui->ipAddressTextbox->setText("127.0.0.1");

    portno = 60001;

    // For when the user clicks the refresh button
    connect(&refreshButton, SIGNAL(clicked(bool)), this, SLOT(refresh()));
}

MainWindow::~MainWindow() {
    for (int i = 0; i < ui->resultsListWidget->count(); i++)
        delete ui->resultsListWidget->item(i);
    delete ui;
}

void MainWindow::scrollDown() {
    ui->resultsListWidget->scrollToBottom();
}

void MainWindow::popupWarning(const QString& info) {
        QMessageBox message(QMessageBox::Warning, "Warning", info);
        message.exec();
}
void MainWindow::popupError(const QString& error) {
        QMessageBox message(QMessageBox::Critical, "Error", error);
        message.exec();
}

void MainWindow::refresh() {
    try {
        localStorage.refresh();
    } catch(std::runtime_error e) {
        this->popupError(e.what());
    }
    int currIndex = ui->stackedWidget->currentIndex();
    if (currIndex == ui->stackedWidget->indexOf(ui->mainStudent))
        this->studentSemesterListPopulate();
    else if (currIndex == ui->stackedWidget->indexOf(ui->courseManager)) {
        this->courseManagerClearLists();
        this->populateSemesterList(ui->courseManagerSemesterList);
    }
    else if (currIndex == ui->stackedWidget->indexOf(ui->contentManagerPage)) {
        this->listManageClear();
        this->populateContentManager();
    }
}



void MainWindow::courseManagerClearLists() {
        ui->courseManagerSemesterList->clear();
        ui->courseManagerCourseList->clear();
        ui->courseManagerCourseTitle->clear();
        ui->courseManagerAddCourseTitle->setText("");
        ui->courseManagerAddCourseCode->setText("");
        ui->courseManagerYear->setText("");
}

void MainWindow::setServerIP() {
    *serverIP = ui->txtServerIP->text();
    ui->statusBar->showMessage("Server IP address set");
}

void MainWindow::displayError(QString error) {
    ui->statusBar->showMessage(error);
}

// FIXME Possible duplicate function?
void MainWindow::populateSemesterList(QListWidget* semesterList) {
    try {
        semesterList->clear();
        foreach (const Class* c, localStorage.getClasses()) {
                if (semesterList->findItems(c->getSemester(), Qt::MatchExactly).empty())
                        semesterList->addItem(c->getSemester());
        }
    }
    catch (std::runtime_error e) {
        this->popupError(e.what());
    }
}

void MainWindow::studentSemesterListPopulate() {
    try {
        ui->semesterList->clear();
        for (int i=0; i < localStorage.getClasses().size(); i++ ){
            const Class* tempclass = localStorage.getClasses().at(i);
            if (ui->semesterList->findItems(tempclass->getSemester(), Qt::MatchExactly).empty())
                    ui->semesterList->addItem(tempclass->getSemester());
        }
    }
    catch (std::runtime_error e) {
        this->popupError(e.what());
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

        // TODO Have a proper standard through the whole system to identify between user account types
        // Check if the user is a student or an admin/content manager
        const QString userType(localStorage.getUser().getType());
        if (userType == QString("student")) {
            // FIXME This looks like in a bad spot?
            this->update_Shopping_Cart_Count();
            this->displayMainStudent();
            this->refresh();
        } else if (userType == QString("content_manager")) {
            ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManagerMain));
        }
    } catch(std::runtime_error e) {
        ui->loginStatus->setText(e.what());
        qDebug() << e.what();
        //ui->loginStatus->setText("Invalid Username and Password");

    }
}

// For when an item is selected in the course manager page bottom left pane
void MainWindow::on_courseManagerSemesterList_itemPressed(QListWidgetItem *item)
{

    this->populateClassList(item->text(), ui->courseManagerCourseList);

}

void MainWindow::populateClassList(QString semester, QListWidget *classList){
    classList->clear();
    try {
        // Add all the courses for our currently selected semester
        foreach (Class* c, localStorage.getClasses()) {
                if (c->getSemester() == semester) {
                        classList->addItem(c->getCourse()->getCourseCode());
                        // const QString* title = &c->getCourse()->getCourseTitle();
                        // ui->courseManagerCourseList->item(ui->courseManagerCourseList->count()-1)->setData(Qt::UserRole, *title);
                        // We will link the actual course
                        QVariant var;
                        var.setValue(c);
                        classList->item(classList->count()-1)->setData(Qt::UserRole, var);
                }
        }
    }
    catch (std::runtime_error e) {
        this->popupError(e.what());
    }
}

void MainWindow::on_courseManagerCourseList_itemPressed(QListWidgetItem *item)
{
        ui->courseManagerCourseTitle->clear();
        ui->courseManagerCourseTitle->setText(item->data(Qt::UserRole).value<Class*>()->getCourse()->getCourseTitle());
}

// For when an item is selected in the semester list on the student main page
void MainWindow::on_semesterList_itemPressed(QListWidgetItem *item)
{
    const QString semester = item->text();
    ui->courseList->clear();
    try {
        // Add all the courses for our currently selected semester
        foreach (Class* c, localStorage.getClasses()) {
            if (c->getSemester() == semester)
                ui->courseList->addItem(c->getCourse()->getCourseCode());
        }
    }
    catch (std::runtime_error e) {
        this->popupError(e.what());
    }

}
// For when an item is selected in the course list
void MainWindow::on_courseList_itemPressed(QListWidgetItem *item)
{
    ui->contentList->clear();

    const QList<Textbook *> *studentContent;

    //Get the booklist
    try {
        studentContent = localStorage.getTextbooks(item->text());
    }
    catch (std::runtime_error e) {
        this->popupError(e.what());
        return;
    }

    foreach (const Textbook *t, *studentContent) {
        if (t->isAvailable()) {
            QListWidgetItem* textbookListItem = new QListWidgetItem(t->getTitle() + (t->isAvailable() ? (" : $" + QString::number(t->getPrice(), 'f', 2) ) : "" ) );
            if (t->isAvailable()) {
                    textbookListItem->setFlags(textbookListItem->flags() | Qt::ItemIsUserCheckable);
                    textbookListItem->setCheckState(Qt::Unchecked);
            } else {
                    textbookListItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            }
            ui->contentList->addItem(textbookListItem);
        }
        foreach (const Chapter *ch, t->getChapters()) {
            if (ch->isAvailable()) {
                QListWidgetItem* chapterListItem = new QListWidgetItem("Ch." + QString::number(ch->getChapterNo()) + ": " + ch->getTitle() + (ch->isAvailable() ? (" : $" + QString::number(ch->getPrice(), 'f', 2) ) : "" ) );
                if (ch->isAvailable()) {
                        chapterListItem->setFlags(chapterListItem->flags() | Qt::ItemIsUserCheckable);
                        chapterListItem->setCheckState(Qt::Unchecked);
                } else {
                        chapterListItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                }
                ui->contentList->addItem(chapterListItem);
            }
            foreach (const Section *s, ch->getSections()) {
                if (s->isAvailable()) {
                    // FIXME HOLY FUCK WHAT WAS I THINKING? Please change this back
                    QString spaces = "";
                    int length = QString("Ch.:" + QString::number(ch->getChapterNo())).length();
                    for (int i = 0; i < length; i++)
                            spaces += " ";
                    spaces += spaces;
                    QListWidgetItem* sectionListItem = new QListWidgetItem(spaces + s->getTitle() + (s->isAvailable() ? (" : $" + QString::number(s->getPrice(), 'f', 2) ) : "" ));
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
}

// DON'T USE THIS IF YOU WISH TO NOT HAVE CHECKBOXES FOR UNAVAILABLE ITEMS
// void MainWindow::on_contentList_itemDoubleClicked(QListWidgetItem *item)

bool MainWindow::validUsernamePassword() {
    return true;
}

bool MainWindow::isStudent() {
    return true;
}

void MainWindow::displayCourseManager() {
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->courseManager));
}

void MainWindow::displayMainStudent() {
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->mainStudent));
}

void MainWindow::on_contentList_itemClicked(QListWidgetItem *item)
{
    const QList<Textbook*> *studentContent;

    try {
        studentContent = localStorage.getTextbooks(ui->courseList->currentItem()->text());
    }
    catch (std::runtime_error e) {
        this->popupError(e.what());
        return;
    }

    int count = 0;
    int index = ui->contentList->currentRow();
    // FIXME count seems a little sketchy here, make sure it's not bugging out
    foreach (const Textbook *t, *studentContent) {
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
                ui->courseDescription->append("\nPrice ");
                ui->courseDescription->setFontUnderline(false);
                ui->courseDescription->append("$" + QString::number(t->getPrice(), 'f', 2));
            }
            ui->courseDescription->setFontUnderline(true);
            ui->courseDescription->append("\nDescription");
            ui->courseDescription->setFontUnderline(false);
            ui->courseDescription->append("\n" + t->getDescription());
            count++;
            break;
        }
        count++;
        foreach (const Chapter *ch, t->getChapters()) {
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
                    ui->courseDescription->append("\nPrice ");
                    ui->courseDescription->setFontUnderline(false);
                    ui->courseDescription->append("$" + QString::number(ch->getPrice(), 'f', 2));
                }
                ui->courseDescription->setFontUnderline(true);
                ui->courseDescription->append("\nDescription");
                ui->courseDescription->setFontUnderline(false);
                ui->courseDescription->append("\n" + ch->getDescription());
                count++;
                break;
            }
            count++;
            foreach (const Section *s, ch->getSections()) {
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
                            ui->courseDescription->append("\nPrice ");
                            ui->courseDescription->setFontUnderline(false);
                            ui->courseDescription->append("$" + QString::number(s->getPrice(), 'f', 2));
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

    const QList<Textbook *> *studentContent;

    try {
        studentContent = localStorage.getTextbooks(ui->courseList->currentItem()->text());
    }
    catch (std::runtime_error e) {
        this->popupError(e.what());
        return;
    }

    foreach (const Textbook *t, *studentContent) {
        if (count == index && index >= 0) {
            shoppingCart.addToCart(t);
            if ( selectedItems.size() > ri ) {
                index = selectedItems.at(ri);
                ri++;
            }
            else
                index = -1;
        }
        count++;
        foreach (const Chapter *ch, t->getChapters()) {
            if (count == index && index >= 0) {
                shoppingCart.addToCart(ch);
                if ( selectedItems.size() > ri ) {
                    index = selectedItems.at(ri);
                    ri++;
                }
                else
                    index = -1;
            }
            count++;
            foreach (const Section *s, ch->getSections()) {
                if (count == index && index >= 0) {
                    shoppingCart.addToCart(s);

                    if ( selectedItems.size() > ri ) {
                        index = selectedItems.at(ri);
                        ri++;
                    }
                    else
                        index = -1;
                }
                count++;
            }
        }
    }
    this->update_Shopping_Cart_Count();
}

void MainWindow::on_btnViewCart_clicked()
{

    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->shoppingCartStudent));
    QList<Content*> content = shoppingCart.getCartContents();
    foreach(Content * c, content){
        QListWidgetItem* contentListItem = new QListWidgetItem(c->getTitle()+" $"+QString::number(c->getPrice(), 'f', 2));
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
    this->update_Shopping_Cart_Count();
    ui->listWidgetShoppingCart->clear();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->mainStudent));
}

void MainWindow::on_btnCheckout_clicked()
{
    if (shoppingCart.getCartContents().count() > 0) {
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->shoppingCartGatherCreditCardInfo));
        //TODO delete the following lines after it works
        ui->lineName->setText("h");
        ui->lineEmail->setText("h");
        ui->linedate->setText("h");
        ui->lineCC->setText("h");
        ui->lineCvv->setText("h");
    } else {
        MainWindow::popupError("There are no items in the Shopping Cart");
    }
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
            MainWindow::popupError("Ensure all fields have been filled");
            ui->billingInfoError->setText("One of your fields is empty or invalid");
            return;
        }
    }
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->shoppingCartOrderConfirmed));
    try{
        checkout.checkout();
    } catch(std::runtime_error e){
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
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->mainStudent));
}

void MainWindow::on_courseManagerDeleteButton_released()
{
    if (ui->courseManagerCourseList->currentItem() == 0)
        return;

    const Class* ass = ui->courseManagerCourseList->currentItem()->data(Qt::UserRole).value<Class*>();

    try {
        // TODO - Remove Class, not remove course
        storageControl.removeCourse(*(ass->getCourse()));
        refresh();
    } catch (std::runtime_error e) {
        this->popupError(e.what());
    }
}

void MainWindow::on_courseManagerAddButton_released() {
    // First check if all fields are set
    // Check if year has its 4 digits

    const QString semester(ui->courseManagerSemesterList2->currentText());
    const QString year(ui->courseManagerYear->text());
    const QString courseCode(ui->courseManagerAddCourseCode->text());
    const QString courseTitle(ui->courseManagerAddCourseTitle->text());

    if (year.contains(" ")) {
            this->popupWarning("You have spaces in the year.");
            return;
    }
    else if (year.length() < 4) {
            this->popupWarning("You didn't write 4 digits for the year.");
            return;
    }
    else if (courseCode.length() < 1) {
            this->popupWarning("Course code is empty.");
            return;
    }
    else if (courseTitle.length() < 1) {
            this->popupWarning("Course title is empty.");
            return;
    }

    // Everything is checked, now we can pass of information to localStorage and get it made
    try {
            localStorage.addCourse(semester, year, courseCode, courseTitle);
            refresh();
    } catch (std::runtime_error e) {
            this->popupError(e.what());
    }
}

void MainWindow::update_Shopping_Cart_Count() {
    ui->shoppingCartCountIndicator->setText("Cart (" + QString::number(shoppingCart.getCartContents().count()) + ")");
}

void MainWindow::clear_All_Widgets() {
    ui->courseList->clear();
    ui->contentList->clear();
    ui->courseDescription->clear();
    ui->listWidgetShoppingCart->clear();
    ui->lineName->clear();
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_actionLogout_triggered()
{
    try {

        const QString userType(localStorage.getUser().getType());

        this->clear_All_Widgets();

        if (userType == "student") {
            shoppingCart.clearCart();
            MainWindow::clearStudentCourseList();
        }

        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->loginPage));
        localStorage.cleanup();
    }
    catch (std::runtime_error e) {
        this->popupError(e.what());
    }
}

void MainWindow::on_btnBackToMain_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->mainStudent));
}

