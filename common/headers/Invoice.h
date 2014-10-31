#ifndef INVOICE_H
#define INVOICE_H
#include "Content.h"
#include "User.h"
#include <vector>
#include <QJsonObject>
#include <QJsonArray>
#include <iterator>

using namespace std;

class Invoice {
  private:
    vector<int> *contentList;
    QString username;
  public:
    Invoice(QString);
    vector<int> *getContentList();
    void addContent(Content*);
    QString getUsername();
    QJsonObject *serialize();
};

#endif // INVOICE_H
