#include "headers/Content.h"

QString Content::getTitle() const {
    return title;
}

float Content::getPrice() const {
    return price;
}

bool Content::isAvailable() const {
    return available;
}

QString Content::getDescription() const {
    return description;
}

int Content::getcid() const {
    return c_id;
}
