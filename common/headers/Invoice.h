#ifndef INVOICE_H
#define INVOICE_H
#include "Content.h"
#include "User.h"

class Invoice{
private:
    Content** contentList;
    User* user;
public:
    Invoice(User*, Content**);
    Content** getContentList();
    User* getUser();
};

#endif // INVOICE_H
