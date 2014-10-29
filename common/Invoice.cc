#include "headers/Invoice.h"

Invoice::Invoice(User *cUser, Content **cContentList) {
  user = cUser;
  contentList = cContentList;
}

Content **Invoice::getContentList() {
  return contentList;
}
User *Invoice::getUser() {
  return user;
}
