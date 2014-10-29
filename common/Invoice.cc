#include "headers/Invoice.h"

Invoice::Invoice(User* cUser, Content** cContentlist){
    user = cUser;
    contentList = cContentList;
}

Content** getContentList(){return contentList;}
User* getUser(){return user;}
