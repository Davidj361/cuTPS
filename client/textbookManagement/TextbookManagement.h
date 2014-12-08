#ifndef TEXTBOOKMANAGEMENT_H
#define TEXTBOOKMANAGEMENT_H

#include <QObject>
#include <QDebug>
#include <stdexcept>

#include "../storage/StorageControl.h"

class TextbookManagement : public QObject {
        Q_OBJECT

    public:
        TextbookManagement(StorageControl *storageControl);

        ~TextbookManagement();

        /* =====================================================================
           Functions : add/edit;
           Purpose   : adds or edits a chapter textbook chapter or section
           Variables : variables contained in a textbook chapter or section
           Returns   : void
        ===================================================================== */
        void addTextbook(QString semester, QString coursecode, QString isbn, QString title, QString publisher, QString author, int year, QString edition, QString description, bool available, float price);
        void editTextbook(QString isbn, QString title, QString publisher, QString author, int year, QString edition, QString description, bool available, float price, int content_id);

        void addChapter(QString title, int chapter, QString textbook, QString description, bool available, float price);
        void editChapter(QString title, int chapter, QString textbook, QString description, bool available, float price, int content_id);

        void addSection(QString title, int sectionNo, int chapterNo, QString isbn, QString description, bool available, float price);
        void editSection(QString title, int sectionNo, int chapterNo, QString isbn, QString description, bool available, float price, int content_id);

        /* =====================================================================
           Functions : delete;
           Purpose   : removes a chapter textbook or section
           Variables : the unique identifier in the databse
           Returns   : void
        ===================================================================== */
        void deleteSection(int content_id);
        void deleteChapter(int content_id);
        void deleteTextbook(int content_id);


    private:

        StorageControl *storageControl;

};

#endif // CONNECTIONCLIENT_H
