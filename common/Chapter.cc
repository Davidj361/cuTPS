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

Textbook* Chapter::getTextbook() {
        return textbook;
}

void Chapter::serialize(QJsonObject & chapterJson){
        chapterJson["title"] = title;
        chapterJson["available"] = available;
        chapterJson["price"] = price;
        chapterJson["chapterNo"] = chapterNo;
        chapterJson["description"] = description;
        chapterJson["c_id"] = c_id;
        chapterJson["ISBN"] = textbook->getISBN();
}

void Chapter::addSection(Section* sec){
        sections.push_back(sec);
}

vector<Section*>& Chapter::getSections(){return this->sections;}

int Chapter::getChapterNo(){
        return chapterNo;
}
