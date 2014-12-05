#ifndef TEXTBOOK_H
#define TEXTBOOK_H
#include "Content.h"
#include "Chapter.h"
#include "Serializable.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QList>

using namespace std;
class Chapter;

class Textbook: public Content, public Serializable {

    public:

        /* =====================================================================
        Function  : Constructor
        Purpose   : Constructs a Textbook
        Variables : IN  -  ISBN
                        -  Title
                        -  Publisher
                        -  Author
                        -  Year
                        -  Edition
                        -  Description
                        -  Whether it is available
                        -  Price
                        -  c_id
        Returns   : void
        ===================================================================== */
        Textbook(QString isbn, QString title, QString publisher, QString author, int year, QString edition, QString description, bool available, float price, int content_id = 0);
        ~Textbook();

        QString getAuthor();
        QString getISBN();
        QString getPublisher();
        QString getEdition();
        QString getDescription();
        int     getYear();
        void serialize(QJsonObject &);
        void addChapter(Chapter *);
        QList<Chapter *>& getChapters();

    private:
        QString author;
        QString ISBN;
        QString publisher;
        QString edition;
        int     year;
        QList<Chapter *> chapters;

};

#endif // TEXTBOOK_H
