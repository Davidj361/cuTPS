#include "headers/Chapter.h"

Chapter::Chapter(QString cTitle, bool cAvailable, float cPrice,
                 int cChapterno, QString cDescription, Textbook *cParent, int cC_id) {
  title = cTitle;
  available = cAvailable;
  price = cPrice;
  description = cDescription;
  chapterNumber = cChapterno;
  textbook = cParent;
  c_id = cC_id;
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
    (*chapterJson)["c_id"] = c_id;
    return chapterJson;
}
