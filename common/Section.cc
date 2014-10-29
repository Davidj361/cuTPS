#include "headers/Section.h"

Section::Section(QString cTitle, bool cAvailable,
                 float cPrice, Textbook *cTextbook,
                 Chapter *cChapter) {
  title = cTitle;
  available = cAvailable;
  price = cPrice;
  textbook = cTextbook;
  chapter = cChapter;
}

Textbook *Section::getTextbook() {
  return textbook;
}

Chapter *Section::getChapter() {
  return chapter;
}
