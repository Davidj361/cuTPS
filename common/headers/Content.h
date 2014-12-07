#ifndef CONTENT_H
#define CONTENT_H
#include <QString>
#include <QJsonObject>

#include "Serializable.h"


class Content: public Serializable {

    public:

        /* =====================================================================
        Function  : Serialize
        Purpose   : Returns a json object structured like
                    {content:{Attributes of the content}}
        Variables : IN/OUT  -  QJsonObject to add attributes to
        Returns   : void
        ===================================================================== */

            // This is not longer needed since Serializable should be doing this
        // virtual void serialize(QJsonObject &) = 0;

        QString getTitle() const;
        float   getPrice() const;
        bool    isAvailable() const;
        QString getDescription() const;
        int     getcid() const;

    protected:
        QString title;
        float   price;
        bool    available;
        QString description;
        int     c_id;

};

#endif // CONTENT_H
