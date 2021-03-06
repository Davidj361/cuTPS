#ifndef CHAPTER_H
#define CHAPTER_H
#include "Content.h"
#include "Section.h"
#include "Textbook.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include <QMetaType>


class Textbook;

class Section;

class Chapter: public Content {

    public:
        friend class Textbook;
        friend class ServerRequestControl; // For fixing memory leaks

        // For setData
        Chapter();
        Chapter(const Chapter&);

        Chapter(QString title, int chapter, Textbook *textbook = 0, QString description = "", bool available = false, float price = 0, int content_id = 0);
        ~Chapter();

        const Textbook *getTextbook() const;
        void serialize(QJsonObject &) const;
        int getChapterNo() const;
        void addSection(Section *);
        const QList<Section *>& getSections() const;

    private:
        int chapterNo;
        Textbook *textbook;
        QList<Section *> sections;

};

Q_DECLARE_METATYPE(Chapter)
Q_DECLARE_METATYPE(Chapter*)

#endif // CHAPTER_H
