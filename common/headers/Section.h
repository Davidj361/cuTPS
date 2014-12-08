#ifndef SECTION_H
#define SECTION_H

#include "Content.h"
#include "Textbook.h"
#include "Chapter.h"
#include <QJsonObject>
#include <QMetaType>

class Chapter;

class Textbook;

class Section: public Content {

    public:
        friend class Chapter;

        /* =====================================================================
        Function  : Section
        Purpose   : Constructs an Section object
        Variables : IN  -  Title
                        -  Section Number
                        -  Parent Chapter
                        -  Parent Textbook
                        -  Description
                        -  Whether it is available for purchase
                        -  Price
                        -  c_id
        Returns   : void
        ===================================================================== */
        // Needed for setData
        Section();
        Section(const Section&);

        Section(QString title, int section, Chapter *chapter = 0, Textbook *textbook = 0, QString description = "", bool available = false, float price = 0, int content_id= 0);

        const Chapter  *getChapter () const;
        const Textbook* getTextbook () const;
        void      serialize (QJsonObject &) const;
        int       getSectionNo() const;

    private:
        int       sectionNo;
        Textbook *textbook;
        Chapter  *chapter;

};

Q_DECLARE_METATYPE(Section)
Q_DECLARE_METATYPE(Section*)

#endif // SECTION_H
