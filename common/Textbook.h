#ifndef TEXTBOOK_H
#define TEXTBOOK_H

class Textbook: public Content{

public:
    Textbook(QString, bool, float, QString, QString, QString, QString, QString, int);
    QString getAuthor();
    QString getISBN();
    QString getPublisher();
    QString getEdition();
    QString getDescription();
    int     getYear();

private:
    QString author;
    QString ISBN;
    QString publisher;
    QString edition;
    QString description;
    int     year;

};

#endif // TEXTBOOK_H
