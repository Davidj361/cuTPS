#include "headers/Textbook.h"

Textbook::Textbook(QString cTitle, bool cAvailable, float cPrice,
                   QString cAuthor, QString cISBN, QString cPublisher,
                   QString cEdition, QString cDescription, int cYear) {
  title = cTitle;
  available = cAvailable;
  price = cPrice;
  author = cAuthor;
  ISBN = cISBN;
  publisher = cPublisher;
  edition = cEdition;
  description = cDescription;
  year = cYear;
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

QJsonObject* Textbook::serialize(){
    QJsonObject *textbookJson = new QJsonObject();
    (*textbookJson)["title"] = title;
    (*textbookJson)["available"] = available;
    (*textbookJson)["price"] = price;
    (*textbookJson)["author"] = author;
    (*textbookJson)["publisher"] = publisher;
    (*textbookJson)["edition"] = edition;
    (*textbookJson)["year"] = year;
    return textbookJson;
}
