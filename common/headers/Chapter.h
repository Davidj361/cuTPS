#ifndef CHAPTER_H
#define CHAPTER_H
#include "Content.h"
#include "Textbook.h"
#include <QJsonObject>

class Chapter: public Content {
  public:
    Chapter(QString, bool, float, int, Textbook *, QString cDescription = "");
    Textbook *getTextbook();
    int getChapterNumber();
    QJsonObject* serialize();
  private:
    int chapterNumber;
    Textbook *textbook;
};

#endif // CHAPTER_H
