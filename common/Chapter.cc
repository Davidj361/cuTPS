#include "headers/Chapter.h"

Chapter::Chapter() : chapterNo(0), textbook(0) {}

Chapter::Chapter(const Chapter& c) : Content(c), chapterNo(c.chapterNo), textbook(c.textbook) {}

Chapter::Chapter(QString cTitle, int cChapterno, Textbook *cParent,
                 QString cDescription, bool cAvailable, float cPrice, int cC_id) {
    title = cTitle;
    available = cAvailable;
    price = cPrice;
    description = cDescription;
    chapterNo = cChapterno;
    textbook = cParent;
    c_id = cC_id;
}

Chapter::~Chapter() {
    foreach (Section *section, sections)
        if (section != 0)
            delete section;
}

const Textbook* Chapter::getTextbook() const {
    return textbook;
}

void Chapter::serialize(QJsonObject &chapterJson) const {
    chapterJson["title"] = title;
    chapterJson["available"] = available;
    chapterJson["price"] = price;
    chapterJson["chapterNo"] = chapterNo;
    chapterJson["description"] = description;

    if (textbook != 0)
        chapterJson["ISBN"] = textbook->getISBN();

    chapterJson["c_id"] = c_id;

    QJsonArray sectionsa;
    foreach(Section* s, sections){
        QJsonObject sjson;
        s->serialize(sjson);
        sectionsa.append(sjson);
    }

    chapterJson["sections"] =sectionsa;

}

void Chapter::addSection(Section *sec) {
    sections.push_back(sec);
}

const QList<Section *>& Chapter::getSections() const {
    return this->sections;
}

int Chapter::getChapterNo() const {
    return chapterNo;
}
