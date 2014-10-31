#ifndef SECTION_H
#define SECTION_H

#include "Content.h"
#include "Textbook.h"
#include "Chapter.h"
#include <QJsonObject>

class Section: public Content {
    public:
        Section(QString, int, Chapter * = 0, Textbook * = 0, QString description = "", bool, float, int cC_id = 0);
        Chapter* getChapter();
        Textbook* getTextbook();
        void serialize(QJsonObject&);
        int getSectionNo();

  private:
    int       sectionNo;
    Textbook *textbook;
    Chapter  *chapter;
};

#endif // SECTION_H
