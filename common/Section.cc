#include "headers/Section.h"

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

Textbook *Section::getTextbook() {
        return textbook;
}

Chapter *Section::getChapter() {
        return chapter;
}

int Section::getSectionNo() {
        return sectionNo;
}

void Section::serialize(QJsonObject& sectionJson){
        QJsonObject content;

        content["title"] = title;
        content["available"] = available;
        content["price"] = price;
        content["sectionNo"] = sectionNo;
        content["description"] = description;
        content["c_id"] = c_id;
        if (textbook != 0)
                content["ISBN"] = textbook->getISBN();
        if (chapter != 0)
                content["chapterNo"] = chapter->getChapterNo();

        sectionJson["content"] = content;
}
