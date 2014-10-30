#ifndef CONTENT_H
#define CONTENT_H
#include <QString>
#include <QJsonObject>


class Content {
  public:
    QString getTitle();
    float   getPrice();
    bool    isAvailable();
    QString getDescription();
    virtual QJsonObject* serialize() = 0;

  protected:
    QString title;
    float   price;
    bool    available;
    QString description;

};

#endif // CONTENT_H
