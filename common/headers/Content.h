#ifndef CONTENT_H
#define CONTENT_H
#include <QString>
#include <QJsonObject>


class Content {

    public:

        /* =====================================================================
        Function  : Serialize
        Purpose   : Returns a json object structured like
                    {content:{Attributes of the content}}
        Variables : IN/OUT  -  QJsonObject to add attributes to
        Returns   : void
        ===================================================================== */
        virtual void serialize(QJsonObject &) = 0;

        QString getTitle();
        float   getPrice();
        bool    isAvailable();
        QString getDescription();
        int     getcid();

    protected:
        QString title;
        float   price;
        bool    available;
        QString description;
        int     c_id;

};

#endif // CONTENT_H
