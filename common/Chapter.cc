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
    for (vector<Section *>::iterator iter = sections.begin(); iter != sections.end(); ++iter) {
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
    QJsonObject content;

    content["title"] = title;
    content["available"] = available;
    content["price"] = price;
    content["chapterNo"] = chapterNo;
    content["description"] = description;
    content["c_id"] = c_id;
    if (textbook != 0)
        content["ISBN"] = textbook->getISBN();
    chapterJson["content"] = content;
}

void Chapter::addSection(Section *sec) {
    sections.push_back(sec);
}

vector<Section *> &Chapter::getSections() {
    return this->sections;
}

int Chapter::getChapterNo() {
    return chapterNo;
}
