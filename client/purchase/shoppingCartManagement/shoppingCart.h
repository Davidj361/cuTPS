#ifndef GUARD_SHOPPINGCART_H
#define GUARD_SHOPPINGCART_H

#include <QList>
#include "Common.h"

class ShoppingCart {
        public:
                void addToCart(const Textbook*);
                void addToCart(const Chapter*);
                void addToCart(const Section*);
                void clearCart();
                const QList<Content*>& getCartContents() const; // for viewing on gui
                QList<int> getCartCids() const; // for client/server sending
        private:
                void cleanup();

                QList<Content*> cartContents;
};

#endif
