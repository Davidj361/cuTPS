#include "headers/Chapter.h"

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
    for (QList<Section *>::iterator iter = sections.begin(); iter != sections.end(); ++iter) {
        if ( (*iter) != 0) {
            delete *iter;
            (*iter) = 0;
        }
    }
}

Textbook *Chapter::getTextbook() {
    return textbook;
}

void Chapter::serialize(QJsonObject &chapterJson) {

    chapterJson["title"] = title;
    chapterJson["available"] = available;
    chapterJson["price"] = price;
    chapterJson["chapterNo"] = chapterNo;
    chapterJson["description"] = description;
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

QList<Section *> &Chapter::getSections() {
    return this->sections;
}

int Chapter::getChapterNo() {
    return chapterNo;
}
