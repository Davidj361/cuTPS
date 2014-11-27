#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QJsonObject>

class Serializable{

public:

    virtual void serialize(QJsonObject &) = 0;

};

#endif
