#ifndef TEXTBOOK_H
#define TEXTBOOK_H
#include "Content.h"
#include <QJsonObject>

class Textbook: public Content {

  public:
    /* =====================================================================
    Function  : Constructor
    Purpose   : Constructs a Textbook
    Variables : IN  -   Title
                IN  -   Whether it is available
                IN  -   Price
                IN  -   Author
                IN  -   ISBN
                IN  -   Publisher
                IN  -   Edition
                IN  -   Description
                IN  -   Year
                IN  -   C_ID Optional
    Returns   : void
    ===================================================================== */
    Textbook(QString, QString, QString, QString, int, QString, QString, bool, float, int cC_id = 0);
    QString getAuthor();
    QString getISBN();
    QString getPublisher();
    QString getEdition();
    QString getDescription();
    int     getYear();
    void serialize(QJsonObject&);

  private:
    QString author;
    QString ISBN;
    QString publisher;
    QString edition;
    int     year;
};

#endif // TEXTBOOK_H
