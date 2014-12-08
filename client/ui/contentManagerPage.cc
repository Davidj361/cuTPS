#include "contentManagerPage.h"
#include "../headers/MainWindow.h"
#include "../ui_mainwindow.h"

void ContentManagerPage::setUi(Ui::MainWindow* ui) {
    this->ui = ui;
}

void MainWindow::on_btnManageContent_clicked()
{
    this->displayManageContent();

}

void MainWindow::on_btnManageAddChapter_clicked()
{
    ui->lineChapterDescription->setText("");
    ui->lineChapterPrice->setText("");
    ui->lineChapterTitle->setText("");
    ui->checkBoxChapterAvailable->setChecked(false);
    ui->btnChapterAddEdit->setText("Add Chapter");
    ui->labelContentNumber->setText("Chapter:");



    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManageChapterForm));

}



void MainWindow::on_btnManageEditChapter_clicked()
{
    Chapter *selectedCh = this->getSelectedChapter(ui->listManageTextbooks, ui->listManageChapters);
    if(selectedCh != 0){
        ui->btnChapterAddEdit->setText("Edit Chapter");
        ui->lineChapterDescription->setText(selectedCh->getDescription());
        ui->lineChapterPrice->setText(QString::number(selectedCh->getPrice(), 'f', 2));
        ui->lineChapterTitle->setText(selectedCh->getTitle());
        ui->checkBoxChapterAvailable->setEnabled(selectedCh->isAvailable());
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
                      getSelectedTextbook(ui->listManageTextbooks),
                      ui->lineChapterDescription->toPlainText(),
                      ui->checkBoxChapterAvailable->isChecked(),
                      (float) ui->lineChapterPrice->text().toDouble(),
                      getSelectedChapter(ui->listManageTextbooks, ui->listManageChapters)->getcid());
            localStorage.editChapter(c);
        }
        if(ui->btnChapterAddEdit->text().compare("Edit Section") == 0){
            Section s(ui->lineChapterTitle->text(),
                      ui->lineChapterNumber->text().toInt(),
                      getSelectedChapter(ui->listManageTextbooks, ui->listManageChapters),
                      getSelectedTextbook(ui->listManageTextbooks),
                      ui->lineChapterDescription->toPlainText(),
                      ui->checkBoxChapterAvailable->isChecked(),
                      (float) ui->lineChapterPrice->text().toDouble(),
                      getSelectedSection(ui->listManageTextbooks, ui->listManageChapters, ui->listManageSections)->getcid());
            localStorage.editSection(s);
        }
        if(ui->btnChapterAddEdit->text().compare("Add Chapter") == 0){
            Chapter c(ui->lineChapterTitle->text(),
                      ui->lineChapterNumber->text().toInt(),
                      getSelectedTextbook(ui->listManageTextbooks),
                      ui->lineChapterDescription->toPlainText(),
                      ui->checkBoxChapterAvailable->isChecked(),
                      (float) ui->lineChapterPrice->text().toDouble());
            localStorage.addChapter(c);
        }
        if(ui->btnChapterAddEdit->text().compare("Add Section") == 0){
            Section s(ui->lineChapterTitle->text(),
                      ui->lineChapterNumber->text().toInt(),
                      getSelectedChapter(ui->listManageTextbooks, ui->listManageChapters),
                      getSelectedTextbook(ui->listManageTextbooks),
                      ui->lineChapterDescription->toPlainText(),
                      ui->checkBoxChapterAvailable->isChecked(),
                      (float) ui->lineChapterPrice->text().toDouble());
            localStorage.addSection(s);
        }
    } catch (std::runtime_error e){
        this->popupError(e.what());
    }
    this->displayManageContent();
}

void MainWindow::on_btnManageAddSection_clicked()
{
    ui->lineChapterDescription->setText("");
    ui->lineChapterPrice->setText("");
    ui->lineChapterTitle->setText("");
    ui->checkBoxChapterAvailable->setChecked(false);
    ui->btnChapterAddEdit->setText("Add Section");
    ui->labelContentNumber->setText("Section:");

    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManageChapterForm));
}

void MainWindow::on_btnManageEditSection_clicked()
{
    Section *s = getSelectedSection(ui->listManageTextbooks, ui->listManageChapters, ui->listManageSections);
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

        ui->listTextbookClass->setEnabled(true);
        ui->listTextbookTerm->setEnabled(true);

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
        ui->listTextbookClass->setEnabled(false);
        ui->listTextbookTerm->setEnabled(false);
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManagerTextbookForm));

    }

}

void MainWindow::on_btnTextbookCancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManagerPage));
}

void MainWindow::on_btnTextbookAddEdit_clicked()
{
    if(ui->listTextbookClass->isEnabled()) {

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
            this->displayManageContent();
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
                    getSelectedTextbook(ui->listManageTextbooks)->getcid());

        try {
            localStorage.editTextbook(tb);
            this->displayManageContent();
        }
        catch (std::runtime_error e){
            this->popupError(e.what());
        }
    }
}

void MainWindow::on_btnManageEditTextbook_clicked()
{
    QList<Class*> classes = localStorage.getClasses();
    QList<Textbook*> tbs;
    foreach(Class *cl, classes){
        tbs.append( cl->getBooklist() );
    }
    int index = ui->listManageTextbooks->currentRow();
    if( index >= 0 ){
        Textbook *selectedTb = tbs.at(index);
        this->displayTextbookPage(selectedTb);
    }
}

void MainWindow::on_listTextbookTerm_itemClicked(QListWidgetItem *item)
{
    this->populateClassList(item->text(), ui->listTextbookClass);
}

void MainWindow::on_btnChapterCancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManagerPage));

}

void MainWindow::displayManageContent(){
    this->listManageClear();

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
        foreach(Textbook *tb, tbs)
            ui->listManageTextbooks->addItem( new QListWidgetItem(tb->getTitle()));
    }

    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->contentManagerPage));

}

void MainWindow::on_btnManageCourses_clicked()
{
    this->displayCourseManager();
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
        }
    }


}

void MainWindow::on_listManageChapters_itemClicked(QListWidgetItem *item)
{
    ui->listManageSections->clear();

    try{
        Chapter* selectedCh = this->getSelectedChapter(ui->listManageTextbooks, ui->listManageChapters);
        if(selectedCh != 0){
            foreach(Section *s, selectedCh->getSections())
                ui->listManageSections->addItem( new QListWidgetItem(s->getTitle()));
        }
    } catch (std::runtime_error e){
        this->popupError(e.what());
    }



}

Textbook* MainWindow::getSelectedTextbook(QListWidget *tblist){
    QList<Class*> classes = localStorage.getClasses();
    QList<Textbook*> tbs;
    foreach(Class *cl, classes){
        tbs.append( cl->getBooklist() );
    }
    int tbIndex = tblist->currentRow();
    if(tbIndex >= 0){
        return tbs.at(tbIndex);
    }

    return 0;
}

Chapter* MainWindow::getSelectedChapter(QListWidget * tblist, QListWidget * chList){
    QList<Class*> classes;
    try {
        classes = localStorage.getClasses();
    }
    catch (std::runtime_error e) {
        throw e;
    }

    QList<Textbook*> tbs;
    foreach(Class *cl, classes){
        tbs.append( cl->getBooklist() );
    }
    int tbIndex = tblist->currentRow();
    if(tbIndex >= 0){
        Textbook *selectedTb = tbs.at(tbIndex);
        int chIndex = chList->currentRow();
        if(chIndex >= 0){
            return selectedTb->getChapters().at(chIndex);
        }
    }
    return 0;
}

void MainWindow::on_btnManageRemoveTextbook_clicked()
{
    try {
        QList<Class *> classes = localStorage.getClasses();
        QList<Textbook*> tbs;
        foreach(Class *cl, classes){
            tbs.append( cl->getBooklist() );
        }
        int index = ui->listManageTextbooks->currentRow();
        if( index >= 0 ){
            Textbook *selectedTb = tbs.at(index);
            localStorage.deleteTextbook(*selectedTb);
            localStorage.refresh();
            this->displayManageContent();
        }
    }
    catch (std::runtime_error e) {
        this->popupError(e.what());
    }
}

void MainWindow::on_btnManageRemoveChapter_clicked()
{

    try {
        QList<Class*> classes = localStorage.getClasses();
        QList<Textbook*> tbs;
        foreach(Class *cl, classes){
            tbs.append( cl->getBooklist() );
        }
        int tbIndex = ui->listManageTextbooks->currentRow();
        if(tbIndex >= 0){
            Textbook *selectedTb = tbs.at(tbIndex);
            int chIndex = ui->listManageChapters->currentRow();
            if(chIndex >= 0){
                Chapter *selectedCh = selectedTb->getChapters().at(chIndex);
                localStorage.deleteChapter(*selectedCh);
                localStorage.refresh();
                this->displayManageContent();
            }
        }
    }
    catch (std::runtime_error e) {
        this->popupError(e.what());
    }
}



void MainWindow::on_btnManageRemoveSection_clicked()
{
    try {

        Section *selectedSec = this->getSelectedSection(ui->listManageTextbooks, ui->listManageChapters, ui->listManageSections);

        localStorage.deleteSection(*selectedSec);

        localStorage.refresh();

        this->displayManageContent();

    }
    catch (std::runtime_error e) {
        this->popupError(e.what());
    }
}

Section * MainWindow::getSelectedSection(QListWidget *tblist, QListWidget *chlist, QListWidget *secList){
    try {
        QList<Class*> classes = localStorage.getClasses();
        QList<Textbook*> tbs;
        foreach(Class *cl, classes){
            tbs.append( cl->getBooklist() );
        }
        int tbIndex = tblist->currentRow();
        if(tbIndex >= 0){
            Textbook *selectedTb = tbs.at(tbIndex);
            int chIndex = chlist->currentRow();
            if(chIndex >= 0){
                Chapter *selectedCh = selectedTb->getChapters().at(chIndex);
                int secIndex = secList->currentRow();
                if(secIndex >= 0){
                    return selectedCh->getSections().at(secIndex);
                }
            }
        }
    }
    catch (std::runtime_error e) {
        throw e;
    }
    return 0;
}
