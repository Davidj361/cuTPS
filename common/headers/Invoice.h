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

        const QList<int> &getContentList() const;
        void addContent(Content *);
        void addContent(int);
        QString getUsername() const;
        void serialize(QJsonObject &) const;

    private:
        QList<int> contentList;
        QString username;

};

#endif // INVOICE_H
