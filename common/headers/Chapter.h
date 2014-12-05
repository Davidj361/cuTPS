#ifndef CHAPTER_H
#define CHAPTER_H
#include "Content.h"
#include "Section.h"
#include "Textbook.h"
#include "Serializable.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QList>

using namespace std;
class Section;
class Textbook;

class Chapter: public Content, public Serializable {

    public:
        Chapter(QString title, int chapter, Textbook *textbook = 0, QString description = "", bool available = false, float price = 0, int content_id = 0);
        ~Chapter();

        Textbook *getTextbook();
        void serialize(QJsonObject &);
        int getChapterNo();
        void addSection(Section *);
        QList<Section *>& getSections();

    private:
        int chapterNo;
        Textbook *textbook;
        QList<Section *> sections;

};

#endif // CHAPTER_H
