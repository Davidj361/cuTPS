#ifndef GUARD_SHOPPINGCART_H
#define GUARD_SHOPPINGCART_H

#include <QList>
#include "Common.h"

class ShoppingCart {
        public:
                void addToCart(Textbook*);
                void addToCart(Chapter*);
                void addToCart(Section*);
                void clearCart();
                const QList<Content*>& getCartContents() const; // for viewing on gui
                QList<int> getCartCids() const; // for client/server sending
        private:
                void cleanup();

                QList<Content*> cartContents;
};

#endif
