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
  public:
    Invoice(QString);
    vector<int> *getContentList();
    void addContent(Content*);
    void addContent(int);
    QString getUsername();
    void serialize(QJsonObject&);
  private:
    vector<int> *contentList;
    QString username;
};

#endif // INVOICE_H
