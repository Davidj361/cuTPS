#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QJsonObject>

class Serializable{

public:

    virtual void serialize(QJsonObject &) const = 0;

};

#endif
