#include "shoppingCart.h"

void ShoppingCart::addToCart(const Textbook* content) {
        // we need to duplicate the data due when user clicks refresh
        // our cart should keep everything

        Content* newContent = new Textbook(*content);
        cartContents.push_back(newContent);
}

void ShoppingCart::addToCart(const Chapter* content) {
        // we need to duplicate the data due when user clicks refresh
        // our cart should keep everything

        Content* newContent = new Chapter(*content);
        cartContents.push_back(newContent);
}

void ShoppingCart::addToCart(const Section* content) {
        // we need to duplicate the data due when user clicks refresh
        // our cart should keep everything

        Content* newContent = new Section(*content);
        cartContents.push_back(newContent);
}

void ShoppingCart::clearCart() {
        this->cleanup();
        cartContents.clear();
}

// for viewing on gui
const QList<Content*>& ShoppingCart::getCartContents() const {
        return this->cartContents;
}

// for client/server sending
QList<int> ShoppingCart::getCartCids() const {
        QList<int> retList;
        // we iterate through our cartContents and retrieve the cid for adding

        for (QList<Content*>::const_iterator iter = cartContents.begin(); iter != cartContents.end(); ++iter) {
                retList.push_back( (*iter)->getcid() );
        }

        return retList;
}

void ShoppingCart::cleanup() {
        for (QList<Content*>::iterator iter = cartContents.begin(); iter != cartContents.end(); ++iter) {
                delete (*iter);
                (*iter) = 0;
        }
}



