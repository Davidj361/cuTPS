#ifndef CHAPTER_H
#define CHAPTER_H
#include "Content.h"
#include "Section.h"
#include "Textbook.h"
#include <QJsonObject>
#include <vector>

using namespace std;
class Section;
class Textbook;

class Chapter: public Content {
  public:
    Chapter(QString, int, Textbook * = 0, QString = "", bool, float, int cC_id = 0);
    Textbook *getTextbook();
    void serialize(QJsonObject&);
    int getChapterNo();
    void addSection(Section*);
    vector<Section*>& getSections();
  private:
    int chapterNo;
    Textbook *textbook;
    vector<Section*> sections;
};

#endif // CHAPTER_H
