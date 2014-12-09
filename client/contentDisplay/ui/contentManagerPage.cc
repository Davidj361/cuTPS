#include "contentManagerPage.h"
#include "MainWindow.h"
#include "ui_mainwindow.h"

void ContentManagerPage::setUi(Ui::MainWindow* ui) {
    this->ui = ui;
}

// Clear is needed if you want to refresh
void MainWindow::listManageClear() {
    ui->listManageChapters->clear();
    ui->listManageSections->clear();
    ui->listManageTextbooks->clear();
}

// For managing courses
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

void MainWindow::on_btnManageContent_clicked()
{
    this->displayManageContent();

}

void MainWindow::on_btnManageAddChapter_clicked()
{
    if (this->getContentManagerSelectedTextbook() == 0)
        return;
    
    ui->lineChapterDescription->setText("");
    ui->lineChapterPrice->setText("");
    ui->lineChapterTitle->setText("");
    ui->lineChapterNumber->setText("");
    ui->checkBoxChapterAvailable->setChecked(false);
    ui->btnChapterAddEdit->setText("Add Chapter");
    ui->labelContentNumber->setText("Chapter:");

    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManageChapterForm));

}



void MainWindow::on_btnManageEditChapter_clicked()
{
    Chapter *selectedCh = this->getContentManagerSelectedChapter();
    if(selectedCh != 0){
        ui->btnChapterAddEdit->setText("Edit Chapter");
        ui->lineChapterDescription->setText(selectedCh->getDescription());
        ui->lineChapterPrice->setText(QString::number(selectedCh->getPrice(), 'f', 2));
        ui->lineChapterTitle->setText(selectedCh->getTitle());
        ui->checkBoxChapterAvailable->setChecked(selectedCh->isAvailable());
        ui->labelContentNumber->setText("Chapter:");
        ui->lineChapterNumber->setText(QString::number(selectedCh->getChapterNo()));

        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManageChapterForm));

    }
}

void MainWindow::on_btnChapterAddEdit_clicked()
{
    try{
        if(ui->btnChapterAddEdit->text().compare("Edit Chapter") == 0){
            // edit chapter
            Chapter c(ui->lineChapterTitle->text(),
                      ui->lineChapterNumber->text().toInt(),
                      getContentManagerSelectedTextbook(),
                      ui->lineChapterDescription->toPlainText(),
                      ui->checkBoxChapterAvailable->isChecked(),
                      (float) ui->lineChapterPrice->text().toDouble(),
                      getContentManagerSelectedChapter()->getcid());
            localStorage.editChapter(c);
            this->displayManageContent();
        }
        if(ui->btnChapterAddEdit->text().compare("Edit Section") == 0){
            Section s(ui->lineChapterTitle->text(),
                      ui->lineChapterNumber->text().toInt(),
                      getContentManagerSelectedChapter(),
                      getContentManagerSelectedTextbook(),
                      ui->lineChapterDescription->toPlainText(),
                      ui->checkBoxChapterAvailable->isChecked(),
                      (float) ui->lineChapterPrice->text().toDouble(),
                      getContentManagerSelectedSection()->getcid());
            localStorage.editSection(s);
            this->displayManageContent();
        }
        if(ui->btnChapterAddEdit->text().compare("Add Chapter") == 0){
            Chapter c(ui->lineChapterTitle->text(),
                      ui->lineChapterNumber->text().toInt(),
                      getContentManagerSelectedTextbook(),
                      ui->lineChapterDescription->toPlainText(),
                      ui->checkBoxChapterAvailable->isChecked(),
                      (float) ui->lineChapterPrice->text().toDouble());
            localStorage.addChapter(c);
            this->displayManageContent();
        }
        if(ui->btnChapterAddEdit->text().compare("Add Section") == 0){
            Section s(ui->lineChapterTitle->text(),
                      ui->lineChapterNumber->text().toInt(),
                      getContentManagerSelectedChapter(),
                      getContentManagerSelectedTextbook(),
                      ui->lineChapterDescription->toPlainText(),
                      ui->checkBoxChapterAvailable->isChecked(),
                      (float) ui->lineChapterPrice->text().toDouble());
            localStorage.addSection(s);
            this->displayManageContent();
        }
    } catch (std::runtime_error e){
        this->popupError(e.what());
    }
}

void MainWindow::on_btnManageAddSection_clicked()
{
    if (this->getContentManagerSelectedTextbook() == 0)
        return;

    ui->lineChapterDescription->setText("");
    ui->lineChapterPrice->setText("");
    ui->lineChapterTitle->setText("");
    ui->lineChapterNumber->setText("");
    ui->checkBoxChapterAvailable->setChecked(false);
    ui->btnChapterAddEdit->setText("Add Section");
    ui->labelContentNumber->setText("Section:");

    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManageChapterForm));
}

void MainWindow::on_btnManageEditSection_clicked()
{
    Section *s = getContentManagerSelectedSection();

    if (s == 0)
        return;
    ui->lineChapterDescription->setText(s->getDescription());
    ui->lineChapterPrice->setText(QString::number(s->getPrice()));
    ui->lineChapterTitle->setText(s->getTitle());
    ui->checkBoxChapterAvailable->setChecked(s->isAvailable());
    ui->btnChapterAddEdit->setText("Edit Section");
    ui->labelContentNumber->setText("Section:");

    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManageChapterForm));
}

void MainWindow::on_btnManageAddTextbook_clicked()
{
    this->displayTextbookPage();
}

void MainWindow::displayTextbookPage(Textbook *tb){
    if(tb == 0){
        // new tb
        ui->lineTextbookDescription->setText("");
        ui->lineTextbookAuthor->setText("");
        ui->lineTextbookEdition->setText("");
        ui->lineTextbookIsbn->setText("");
        ui->lineTextbookPrice->setText("");
        ui->lineTextbookPublisher->setText("");
        ui->lineTextbookTitle->setText("");
        ui->lineTextbookYear->setText("");
        ui->checkBoxTextbookAvailable->setChecked(false);
        ui->btnTextbookAddEdit->setText("Add Textbook");
        this->populateSemesterList(ui->listTextbookTerm);
        ui->labelClass->setText("Class");
        ui->labelSemester->setText("Semester");

        ui->listTextbookClass->setVisible(true);
        ui->listTextbookTerm->setVisible(true);

        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManagerTextbookForm));

    }
    else{
        ui->lineTextbookDescription->setText(tb->getDescription());
        ui->lineTextbookAuthor->setText(tb->getAuthor());
        ui->lineTextbookEdition->setText(tb->getEdition());
        ui->lineTextbookIsbn->setText(tb->getISBN());
        ui->lineTextbookPrice->setText(QString::number(tb->getPrice(), 'f', 2));
        ui->lineTextbookPublisher->setText(tb->getPublisher());
        ui->lineTextbookTitle->setText(tb->getTitle());
        qDebug() << " cid is "<<tb->getcid();
        ui->lineTextbookYear->setText(QString::number(tb->getYear()));
        bool checked = tb->isAvailable();
        ui->checkBoxTextbookAvailable->setChecked(checked);
        ui->btnTextbookAddEdit->setText("Edit Textbook");
        ui->listTextbookClass->setVisible(false);
        ui->labelClass->setText("");
        ui->labelSemester->setText("");

        ui->listTextbookTerm->setVisible(false);


        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManagerTextbookForm));


    }

}

void MainWindow::on_btnTextbookCancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManagerPage));
}

void MainWindow::on_btnTextbookAddEdit_clicked()
{
    if(ui->listTextbookClass->isVisible()) {

        if (ui->listTextbookTerm->currentRow() < 0) {
            this->popupWarning("Please select a semester");
            return;
        }

        if (ui->listTextbookClass->currentRow() < 0) {
            this->popupWarning("Please select a course");
            return;
        }

        Course* course = new Course(ui->listTextbookClass->selectedItems().first()->text(), "");

        Class c(ui->listTextbookTerm->selectedItems().first()->text(), course);

        Textbook* tb = new Textbook(
                    ui->lineTextbookIsbn->text(),
                    ui->lineTextbookTitle->text(),
                    ui->lineTextbookPublisher->text(),
                    ui->lineTextbookAuthor->text(),
                    ui->lineTextbookPrice->text().toInt(),
                    ui->lineTextbookEdition->text(),
                    ui->lineTextbookDescription->toPlainText(),
                    ui->checkBoxTextbookAvailable->isChecked(),
                    (float) ui->lineTextbookPrice->text().toDouble()
                    );

        c.addTextbook(tb);

        try {
            localStorage.addTextbook(c);
        }
        catch (std::runtime_error e){
            this->popupError(e.what());
        }
    }

    else{
        // edit
        Textbook tb(
                    ui->lineTextbookIsbn->text(),
                    ui->lineTextbookTitle->text(),
                    ui->lineTextbookPublisher->text(),
                    ui->lineTextbookAuthor->text(),
                    ui->lineTextbookPrice->text().toInt(),
                    ui->lineTextbookEdition->text(),
                    ui->lineTextbookDescription->toPlainText(),
                    ui->checkBoxTextbookAvailable->isChecked(),
                    (float) ui->lineTextbookPrice->text().toDouble(),
                    getContentManagerSelectedTextbook()->getcid());

        try {
            localStorage.editTextbook(tb);
        }
        catch (std::runtime_error e){
            this->popupError(e.what());
        }
    }
    this->displayManageContent();
}

void MainWindow::on_btnManageEditTextbook_clicked()
{

    Textbook* tb = this->getContentManagerSelectedTextbook();
    if (tb != 0)
        this->displayTextbookPage(tb);

}

void MainWindow::on_listTextbookTerm_itemClicked(QListWidgetItem *item)
{
    this->populateClassList(item->text(), ui->listTextbookClass);
}

void MainWindow::on_btnChapterCancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManagerPage));

}

void MainWindow::populateContentManager() {
    QList<Class*> classes;
    try {
        classes = localStorage.getClasses();
    }
    catch (std::runtime_error e) {
        this->popupError(e.what());
        return;
    }

    foreach(Class *cl, classes){
        QList<Textbook*> tbs = cl->getBooklist();
        foreach(Textbook *tb, tbs) {
            ui->listManageTextbooks->addItem( new QListWidgetItem(tb->getTitle()));
            // setData should be used for easier memory management and less overhead
            QVariant var;
            var.setValue(tb);
            ui->listManageTextbooks->item(ui->listManageTextbooks->count()-1)->setData(Qt::UserRole, var);
        }
    }
}

void MainWindow::displayManageContent(){
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManagerPage));
    this->refresh();
}

void MainWindow::on_listManageTextbooks_itemClicked(QListWidgetItem *item)
{
    QList<Class*> classes;
    try {
        classes = localStorage.getClasses();
    }
    catch (std::runtime_error e) {
        this->popupError(e.what());
        return;
    }

    QList<Textbook*> tbs;
    foreach(Class *cl, classes){
        tbs.append( cl->getBooklist() );
    }
    int tbIndex = ui->listManageTextbooks->currentRow();
    if(tbIndex >= 0){
        Textbook *selectedTb = tbs.at(tbIndex);
        ui->listManageChapters->clear();
        ui->listManageSections->clear();
        foreach(Chapter *ch, selectedTb->getChapters()){
            ui->listManageChapters->addItem( new QListWidgetItem(ch->getTitle()));
            QVariant var;
            var.setValue(ch);
            ui->listManageChapters->item(ui->listManageChapters->count()-1)->setData(Qt::UserRole, var);
        }
    }


}

void MainWindow::on_listManageChapters_itemClicked(QListWidgetItem *item)
{
    ui->listManageSections->clear();

    try{
        Chapter* selectedCh = this->getContentManagerSelectedChapter();
        if(selectedCh != 0){
            foreach(Section *s, selectedCh->getSections()) {
                ui->listManageSections->addItem( new QListWidgetItem(s->getTitle()));
                QVariant var;
                var.setValue(s);
                ui->listManageSections->item(ui->listManageSections->count()-1)->setData(Qt::UserRole, var);
            }
        }
    } catch (std::runtime_error e){
        this->popupError(e.what());
    }



}

Textbook* MainWindow::getContentManagerSelectedTextbook() {

    QListWidgetItem* item = ui->listManageTextbooks->currentItem();
    if (item != 0) {
        return item->data(Qt::UserRole).value<Textbook*>();
    }

    return 0;
}

Chapter* MainWindow::getContentManagerSelectedChapter() {

    QListWidgetItem* item = ui->listManageChapters->currentItem();
    if (item != 0) {
        return item->data(Qt::UserRole).value<Chapter*>();
    }

    return 0;
}

Section * MainWindow::getContentManagerSelectedSection() {

    QListWidgetItem* item = ui->listManageSections->currentItem();
    if (item != 0) {
        return item->data(Qt::UserRole).value<Section*>();
    }
 
    return 0;
}

void MainWindow::on_btnManageRemoveTextbook_clicked()
{
    try {
        Textbook* tb = getContentManagerSelectedTextbook();
        if (tb != 0)
            localStorage.deleteTextbook(*tb);
        this->refresh();
    } catch (std::runtime_error e) {
        this->popupError(e.what());
    }

}

void MainWindow::on_btnManageRemoveChapter_clicked()
{
    try {
        Chapter* ch = getContentManagerSelectedChapter();
        if (ch != 0)
            localStorage.deleteChapter(*ch);
        this->refresh();
    } catch (std::runtime_error e) {
        this->popupError(e.what());
    }

}

void MainWindow::on_btnManageRemoveSection_clicked()
{
    try {
        Section *selectedSec = this->getContentManagerSelectedSection();
        if (selectedSec != 0)
            localStorage.deleteSection(*selectedSec);
        this->refresh();
    }
    catch (std::runtime_error e) {
        this->popupError(e.what());
    }
}

void MainWindow::on_btnManageBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManagerMain));
}

void MainWindow::on_btnCourseManageBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManagerMain));
}
