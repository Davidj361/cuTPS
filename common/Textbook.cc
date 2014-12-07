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

const QString& Textbook::getAuthor() const {
    return author;
}

const QString& Textbook::getISBN() const {
    return ISBN;
}

const QString& Textbook::getPublisher() const {
    return publisher;
}

const QString& Textbook::getEdition()const {
    return edition;
}

const QString& Textbook::getDescription() const {
    return description;
}

int Textbook::getYear() const {
    return year;
}

void Textbook::addChapter(Chapter *cha) {
    chapters.push_back(cha);
}

const QList<Chapter *>& Textbook::getChapters() const {
    return chapters;
}

void Textbook::serialize(QJsonObject &content) const {

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

    QJsonArray chs;
    foreach(Chapter * c, chapters){
        QJsonObject cjson;
        c->serialize(cjson);
        chs.append(cjson);
    }

    content["chapters"] = chs;
}
