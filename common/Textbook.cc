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

void Textbook::addChapter(Chapter * cha){
  chapters->push_back(cha);
}

vector<Chapter*>& Textbook::getChapters(){return chapters;}
void Textbook::serialize(QJsonObject& textbookJson){
    textbookJson["title"] = title;
    textbookJson["available"] = available;
    textbookJson["price"] = price;
    textbookJson["author"] = author;
    textbookJson["publisher"] = publisher;
    textbookJson["edition"] = edition;
    textbookJson["year"] = year;
    textbookJson["c_id"] = c_id;
    textbookJson["ISBN"] = ISBN;
    textbookJson["description"] = description;
}
