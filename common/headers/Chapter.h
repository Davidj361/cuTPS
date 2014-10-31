#ifndef CHAPTER_H
#define CHAPTER_H
#include "Content.h"
#include "Textbook.h"
#include <QJsonObject>

class Chapter: public Content {
  public:
    Chapter(QString, bool, float, int, QString cDescription = "", Textbook * = 0, int cC_id = 0);
    Textbook *getTextbook();
    QJsonObject* serialize();
    int getChapterNo();
  private:
    int chapterNo;
    Textbook *textbook;
};

#endif // CHAPTER_H
