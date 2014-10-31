#ifndef SECTION_H
#define SECTION_H
#include "Content.h"
#include "Textbook.h"
#include "Chapter.h"
#include <QJsonObject>

class Section: public Content {
    public:
        Section(QString, bool, float, int, QString description = "",Textbook * = 0, Chapter * = 0, int cC_id = 0);
        Chapter* getChapter();
        Textbook* getTextbook();
        QJsonObject* serialize();
        int getSectionNo();

  private:
    int       sectionNo;
    Textbook *textbook;
    Chapter  *chapter;
};

#endif // SECTION_H
