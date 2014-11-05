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

QString Content::getDescription() {
    return description;
}

int Content::getcid() {
    return c_id;
}
