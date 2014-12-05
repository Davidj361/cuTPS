#ifndef SECTION_H
#define SECTION_H

#include "Content.h"
#include "Textbook.h"
#include "Chapter.h"
#include "Serializable.h"
#include <QJsonObject>

class Chapter;
class Textbook;

class Section: public Content, public Serializable {

    public:
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
        Section(QString title, int section, Chapter *chapter = 0, Textbook *textbook = 0, QString description = "", bool available = false, float price = 0, int content_id= 0);
        Chapter  *getChapter ();
        Textbook *getTextbook ();
        void      serialize (QJsonObject &);
        int       getSectionNo();

    private:
        int       sectionNo;
        Textbook *textbook;
        Chapter  *chapter;

};

#endif // SECTION_H
