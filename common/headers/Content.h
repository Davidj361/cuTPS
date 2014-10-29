#ifndef CONTENT_H
#define CONTENT_H
#include <QString>

class Content{
    public:
        QString getTitle();
        float   getPrice();
        bool    isAvailable();


    protected:
        QString title;
        float   price;
        bool    available;


};

#endif // CONTENT_H
