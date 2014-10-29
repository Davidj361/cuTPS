#include "headers/Content.h"

QString Content::getTitle() {
  return title;
}

float Content::getPrice() {
  return price;
}

bool Content::isAvailable() {
  return available;
}
