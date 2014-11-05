#ifndef TEXTBOOK_H
#define TEXTBOOK_H
#include "Content.h"
#include "Chapter.h"
#include <QJsonObject>
#include <vector>

using namespace std;
class Chapter;

class Textbook: public Content {

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
    Textbook(QString, QString, QString, QString, int, QString, QString, bool, float, int cC_id = 0);
    ~Textbook();

    QString getAuthor();
    QString getISBN();
    QString getPublisher();
    QString getEdition();
    QString getDescription();
    int     getYear();
    void serialize(QJsonObject&);
    void addChapter(Chapter *);
    vector<Chapter*>& getChapters();

  private:
    QString author;
    QString ISBN;
    QString publisher;
    QString edition;
    int     year;
    vector<Chapter*> chapters;

};

#endif // TEXTBOOK_H
