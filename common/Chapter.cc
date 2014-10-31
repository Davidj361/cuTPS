#include "headers/Chapter.h"

Chapter::Chapter(QString cTitle, bool cAvailable, float cPrice,
                 int cChapterno, Textbook *cParent, QString cDescription) {
  title = cTitle;
  available = cAvailable;
  price = cPrice;
  description = cDescription;
  chapterNumber = cChapterno;
  textbook = cParent;
}

Textbook* Chapter::getTextbook() {
  return textbook;
}

int Chapter::getChapterNumber() {
    return chapterNumber;
}

QJsonObject* Chapter::serialize(){

    QJsonObject *chapterJson = new QJsonObject();
    (*chapterJson)["title"] = title;
    (*chapterJson)["available"] = available;
    (*chapterJson)["price"] = price;
    (*chapterJson)["chapterNumber"] = chapterNumber;
    (*chapterJson)["description"] = description;
    return chapterJson;
}
