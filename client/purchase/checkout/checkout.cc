#include "checkout.h"

Checkout::Checkout(const StorageControl& storage, ShoppingCart& cart, const LocalStorage& lStorage) : storage(&storage), cart(&cart), lStorage(&lStorage) {}

// This will send off the invoice object to StorageControl
void Checkout::checkout() {
        // check if subsystems are not null
        if (storage == 0 || cart == 0 || lStorage == 0)
                throw std::runtime_error("Checkout::checkout, storage, lStorage, or cart is null");
        Invoice invoice(lStorage->getUser().getUsername(), cart->getCartCids());
        try{
            storage->checkout(invoice);
            cart->clearCart();
        }
        catch(std::runtime_error e){
            throw e;
        }
}
