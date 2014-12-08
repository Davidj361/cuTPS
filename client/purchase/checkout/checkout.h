#ifndef GUARD_CHECKOUT_H
#define GUARD_CHECKOUT_H

#include "../../storage/StorageControl.h"
#include "../../contentDisplay/localStorage/localStorage.h"
#include "../shoppingCartManagement/shoppingCart.h"
#include "../../../common/headers/Textbook.h"
#include "../../../common/headers/Chapter.h"
#include "../../../common/headers/Section.h"
#include "../../../common/headers/User.h"
#include "../../../common/headers/Course.h"
#include "../../../common/headers/Invoice.h"

class Checkout {
        public:

                Checkout(const StorageControl&, ShoppingCart&, const LocalStorage&);

                /* =====================================================================
                   Function  : checkout;
                   Purpose   : creates invoice from contents of shopping cart
                   Returns   : void
                ===================================================================== */
                void checkout();

        private:

                const StorageControl*const storage;
                ShoppingCart* const cart;
                const LocalStorage*const lStorage;
};

#endif
