#ifndef SECTION_H
#define SECTION_H
#include "Content.h"
#include "Textbook.h"
#include "Chapter.h"

class Section: public Content{
    Section(QString, bool, float, Textbook*, Chapter*);
    Chapter* getChapter();
    Textbook* getTextbook();
private:
    int       sectionNo;
    Textbook* textbook;
    Chapter*  chapter;
};

#endif // SECTION_H
