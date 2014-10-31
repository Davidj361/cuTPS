#ifndef TEXTBOOK_H
#define TEXTBOOK_H
#include "Content.h"
#include <QJsonObject>

class Textbook: public Content {

  public:
    Textbook(QString, bool, float, QString, QString, QString, QString, QString, int);
    QString getAuthor();
    QString getISBN();
    QString getPublisher();
    QString getEdition();
    QString getDescription();
    int     getYear();
    QJsonObject* serialize();

  private:
    QString author;
    QString ISBN;
    QString publisher;
    QString edition;
    int     year;
};

#endif // TEXTBOOK_H
