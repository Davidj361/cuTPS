#include "headers/Section.h"

Section::Section(QString cTitle, bool cAvailable,
                 float cPrice,int cSectionNo, QString cDescription, Textbook *cTextbook,
                 Chapter *cChapter, int cC_id) {
  title = cTitle;
  available = cAvailable;
  price = cPrice;
  sectionNo = cSectionNo;
  textbook = cTextbook;
  chapter = cChapter;
  description = cDescription;
  c_id = cC_id;
}

Textbook *Section::getTextbook() {
  return textbook;
}

Chapter *Section::getChapter() {
  return chapter;
}

int Section::getSectionNo() {
    return sectionNo;
}

QJsonObject* Section::serialize(){
    QJsonObject *sectionJson = new QJsonObject();
    (*sectionJson)["title"] = title;
    (*sectionJson)["available"] = available;
    (*sectionJson)["price"] = price;
    (*sectionJson)["sectionNo"] = sectionNo;
    (*sectionJson)["description"] = description;
    (*sectionJson)["c_id"] = c_id;
    (*sectionJson)["ISBN"] = textbook->getISBN();
    (*sectionJson)["chapterNo"] = chapter->getChapterNo();
    return sectionJson;
}
