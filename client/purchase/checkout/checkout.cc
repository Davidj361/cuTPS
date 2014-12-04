#include "checkout.h"

Checkout::Checkout(const StorageControl& storage, const ShoppingCart& cart, const LocalStorage& lStorage) : storage(&storage), cart(&cart), lStorage(&lStorage) {}

// This will send off the invoice object to StorageControl
void Checkout::checkout() {
        // check if subsystems are not null
        if (storage == 0 || cart == 0 || lStorage == 0)
                throw runtime_error("Checkout::checkout, storage, lStorage, or cart is null");
        Invoice invoice(lStorage->getUser().getUsername(), cart->getCartCids());
        storage->checkout(invoice);
}
