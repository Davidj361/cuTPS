#ifndef SECTION_H
#define SECTION_H
#include "Content.h"
#include "Textbook.h"
#include "Chapter.h"
#include <QJsonObject>

class Section: public Content {
    Section(QString, bool, float, int,Textbook *, Chapter *, QString description = "");
    Chapter* getChapter();
    Textbook* getTextbook();
    QJsonObject* serialize();

  private:
    int       sectionNo;
    Textbook *textbook;
    Chapter  *chapter;
};

#endif // SECTION_H
