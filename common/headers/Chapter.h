#ifndef CHAPTER_H
#define CHAPTER_H
#include "Content.h"
#include "Textbook.h"
#include <QJsonObject>

class Chapter: public Content {
  public:
    Chapter(QString, int, Textbook * = 0, QString = "", bool, float, int cC_id = 0);
    Textbook *getTextbook();
    void serialize(QJsonObject&);
    int getChapterNo();
  private:
    int chapterNo;
    Textbook *textbook;
};

#endif // CHAPTER_H
