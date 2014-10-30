#ifndef CHAPTER_H
#define CHAPTER_H
#include "Content.h"
#include "Textbook.h"
#include <QJsonObject>

class Chapter: public Content {
  public:
    Chapter(QString, bool, float, int, Textbook *, QString cDescription = "");
    Textbook *getTextbook();
    QJsonObject* serialize();
  private:
    int chapterNo;
    Textbook *textbook;
};

#endif // CHAPTER_H
