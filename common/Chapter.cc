#include "headers/Chapter.h"

Chapter::Chapter(QString cTitle, bool cAvailable,
                 float cPrice, int cChapterno,
                 Textbook* cParent){
    title = cTitle;
    available = cAvailable;
    price = cPrice;
    chapterNo = cChapterno;
    textbook = cParent;
}

Textbook* Chapter::getTextbook(){return textbook;}
