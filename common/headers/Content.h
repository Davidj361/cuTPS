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
    int     getcid();
    virtual void serialize(QJsonObject&) = 0;

  protected:
    QString title;
    float   price;
    bool    available;
    QString description;
    int     c_id;

};

#endif // CONTENT_H
