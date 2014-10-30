#include "headers/Chapter.h"

Chapter::Chapter(QString cTitle, bool cAvailable, float cPrice,
                 int cChapterno, Textbook *cParent, QString cDescription) {
  title = cTitle;
  available = cAvailable;
  price = cPrice;
  description = cDescription;
  chapterNo = cChapterno;
  textbook = cParent;
}

Textbook* Chapter::getTextbook() {
  return textbook;
}

QJsonObject* Chapter::serialize(){

    QJsonObject *chapterJson = new QJsonObject();
    (*chapterJson)["title"] = title;
    (*chapterJson)["available"] = available;
    (*chapterJson)["price"] = price;
    (*chapterJson)["chapterNo"] = chapterNo;
    (*chapterJson)["description"] = description;
    return chapterJson;
}
