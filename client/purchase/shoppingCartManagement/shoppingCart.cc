#include "shoppingCart.h"

void ShoppingCart::addToCart( const Textbook* content ) {

    if ( !contains(content->getcid()) ) {
        Content* newContent = new Textbook(*content);
        cartContents.push_back(newContent);
    }

}

void ShoppingCart::addToCart( const Chapter* content ) {

    if (!contains(content->getcid())) {
        Content* newContent = new Chapter(*content);
        cartContents.push_back(newContent);
    }

}

void ShoppingCart::addToCart( const Section* content ) {

    if (!contains(content->getcid())) {
        Content* newContent = new Section(*content);
        cartContents.push_back(newContent);
    }

}

void ShoppingCart::clearCart() {

    this->cleanup();
    cartContents.clear();

}

const QList<Content*>& ShoppingCart::getCartContents() const {

    return this->cartContents;

}

QList<int> ShoppingCart::getCartCids() const {

    QList<int> retList;

    foreach (Content *content, cartContents)
        retList.push_back(content->getcid());

    return retList;

}

void ShoppingCart::cleanup() {

    foreach(Content *c, cartContents){
        delete c;
        c = 0;
    }

}

bool ShoppingCart::contains(int c_id) {

    foreach (Content *content, cartContents) {
        if (content->getcid() == c_id)
            return true;
    }

    return false;

}

