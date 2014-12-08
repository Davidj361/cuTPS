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

        /* =====================================================================
           Function  : addtocart
           Purpose   : adds something with a cid to the cart
           Returns   : void
        ===================================================================== */
        void addToCart(const Textbook*);
        void addToCart(const Chapter*);
        void addToCart(const Section*);

        /* =====================================================================
           Function  : clearcart
           Purpose   : removes everything in the cart
           Returns   : void
        ===================================================================== */
        void clearCart();

        /* =====================================================================
           Function  : getCartContents
           Purpose   : returns the objects that are in the cart
           Returns   : QList<Content*>
        ===================================================================== */
        const QList<Content*>& getCartContents() const;

        /* =====================================================================
           Function  : getCartCids
           Purpose   : returns the cids of the objects in the cart for invoicing
           Returns   : QList<int>
        ===================================================================== */
        QList<int> getCartCids() const;

    private:
        void cleanup();
        bool contains(int c_id);

        QList<Content*> cartContents;
};

#endif
