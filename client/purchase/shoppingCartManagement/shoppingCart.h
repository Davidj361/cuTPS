#ifndef GUARD_SHOPPINGCART_H
#define GUARD_SHOPPINGCART_H

#include <QList>
#include "../../../common/headers/Textbook.h"
#include "../../../common/headers/Chapter.h"
#include "../../../common/headers/Section.h"
#include "../../../common/headers/User.h"
#include "../../../common/headers/Course.h"

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
        bool contains(int c_id);

        QList<Content*> cartContents;
};

#endif
