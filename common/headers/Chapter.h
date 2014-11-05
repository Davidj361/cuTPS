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

    /* =====================================================================
    Function  : Chapter
    Purpose   : Constructs a Chapter
    Variables : IN  -  Title
                IN  -  Chapter Number
                IN  -  Parent Textbook
                IN  -  Description
                IN  -  Whether it is available
                IN  -  Price
                IN  -  c_id
    Returns   : void
    ===================================================================== */
    Chapter(QString, int, Textbook * = 0, QString = "", bool = false, float = 0, int cC_id = 0);
    ~Chapter();
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
