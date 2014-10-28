#ifndef CONTENT_H
#define CONTENT_H
#include <QString>

class Content{
    public:
        virtual ~Content();
        QString getTitle();
        float   getPrice();
        bool    isAvailable();


    private:
        QString title;
        float   price;
        bool    available;


};

#endif // CONTENT_H
