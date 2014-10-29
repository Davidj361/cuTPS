#ifndef CHAPTER_H
#define CHAPTER_H
#include "Content.h"
#include "Textbook.h"

class Chapter: public Content{
public:
    Chapter(QString, bool, float, int, Textbook*);
    Textbook* getTextbook();
private:
    int chapterNo;
    Textbook *textbook;
};

#endif // CHAPTER_H
