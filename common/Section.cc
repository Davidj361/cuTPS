#include "headers/Section.h"

Section::Section() : sectionNo(0), textbook(0), chapter(0) {}

Section::Section(const Section& s) : Content(s), sectionNo(s.sectionNo), textbook(s.textbook), chapter(s.chapter) {}

Section::Section(QString cTitle, int cSectionNo, Chapter *cChapter,
                 Textbook *cTextbook, QString cDescription, bool cAvailable,
                 float cPrice, int cC_id) {
    title = cTitle;
    available = cAvailable;
    price = cPrice;
    sectionNo = cSectionNo;
    textbook = cTextbook;
    chapter = cChapter;
    description = cDescription;
    c_id = cC_id;
}

const Textbook* Section::getTextbook () const {
    return textbook;
}

const Chapter* Section::getChapter () const {
    return chapter;
}

int Section::getSectionNo() const {
    return sectionNo;
}

void Section::serialize(QJsonObject &sectionJson) const {

    sectionJson["title"] = title;
    sectionJson["available"] = available;
    sectionJson["price"] = price;
    sectionJson["sectionNo"] = sectionNo;
    sectionJson["description"] = description;
    sectionJson["c_id"] = c_id;
    if(textbook != 0){
        sectionJson["ISBN"] = textbook->getISBN();
    }
    if (chapter != 0) {
        sectionJson["chapterNo"] = chapter->getChapterNo();
    }

}
