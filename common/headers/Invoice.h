#ifndef INVOICE_H
#define INVOICE_H
#include "Content.h"
#include "User.h"
#include "Serializable.h"
#include <QList>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QList>
#include <iterator>

using namespace std;

class Invoice: public Serializable {

    public:

        /* =====================================================================
        Function  : Invoice
        Purpose   : Constructs an Invoice object
        Variables : IN  -  Username
        Returns   : void
        ===================================================================== */
        Invoice(const QString&);
        Invoice(const QString&, const QList<int>&); // this is for constructing from the shopping cart

        QList<int> &getContentList();
        void addContent(Content *);
        void addContent(int);
        QString getUsername();
        void serialize(QJsonObject &);

    private:
        QList<int> contentList;
        QString username;

};

#endif // INVOICE_H
