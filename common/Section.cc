#include "headers/Section.h"

Section::Section(QString cTitle, bool cAvailable,
                 float cPrice,int cSectionNo, Textbook *cTextbook,
                 Chapter *cChapter, QString cDescription) {
  title = cTitle;
  available = cAvailable;
  price = cPrice;
  sectionNo = cSectionNo;
  textbook = cTextbook;
  chapter = cChapter;
  description = cDescription;
}

Textbook *Section::getTextbook() {
  return textbook;
}

Chapter *Section::getChapter() {
  return chapter;
}

QJsonObject* Section::serialize(){
    QJsonObject *sectionJson = new QJsonObject();
    (*sectionJson)["title"] = title;
    (*sectionJson)["available"] = available;
    (*sectionJson)["price"] = price;
    (*sectionJson)["sectionNo"] = sectionNo;
    (*sectionJson)["description"] = description;
    return sectionJson;
}
