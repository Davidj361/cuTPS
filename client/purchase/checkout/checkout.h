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

// This class will generate invoices as well as make calls to StorageControl subsystem
class Checkout {
        public:
                // Using this, we can have direct links to other subsystems without needing to create more than 1
                // instance of each for our system
                Checkout(const StorageControl&, ShoppingCart&, const LocalStorage&);
                // This will send off the invoice object to StorageControl
                // TODO See if you can change return type for error checking success or fail?
                void checkout();
        private:
                // Pointers to our subsystems for calling functions
                const StorageControl*const storage;
                ShoppingCart* const cart;
                const LocalStorage*const lStorage;
};

#endif
