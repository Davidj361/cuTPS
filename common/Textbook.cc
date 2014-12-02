    #include "headers/Textbook.h"

Textbook::Textbook(QString cISBN, QString cTitle, QString cPublisher, QString cAuthor,
                   int cYear, QString cEdition, QString cDescription,
                   bool cAvailable, float cPrice, int cC_id) {
    title = cTitle;
    available = cAvailable;
    price = cPrice;
    author = cAuthor;
    ISBN = cISBN;
    publisher = cPublisher;
    edition = cEdition;
    description = cDescription;
    year = cYear;
    c_id = cC_id;
}

Textbook::~Textbook() {
    for (QList<Chapter *>::iterator iter = chapters.begin(); iter != chapters.end(); ++iter) {
        if ( (*iter) != 0) {
            delete *iter;
            (*iter) = 0;
        }
    }
}

QString Textbook::getAuthor() {
    return author;
}

QString Textbook::getISBN() {
    return ISBN;
}

QString Textbook::getPublisher() {
    return publisher;
}

QString Textbook::getEdition() {
    return edition;
}

QString Textbook::getDescription() {
    return description;
}

int     Textbook::getYear() {
    return year;
}

void Textbook::addChapter(Chapter *cha) {
    chapters.push_back(cha);
}

QList<Chapter *> &Textbook::getChapters() {
    return chapters;
}
void Textbook::serialize(QJsonObject &content) {

    content["title"] = title;
    content["available"] = available;
    content["price"] = price;
    content["author"] = author;
    content["publisher"] = publisher;
    content["edition"] = edition;
    content["year"] = year;
    content["c_id"] = c_id;
    content["ISBN"] = ISBN;
    content["description"] = description;
}
