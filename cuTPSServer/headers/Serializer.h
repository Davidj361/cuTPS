#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <iostream>
#include <string>
#include <stdexcept>

#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

#include "../../common/headers/Definitions.h"

using namespace std;

class Serializer {
  public:
    Serializer();
    ~Serializer();

    /* =====================================================================
    Function  : Deserialize
    Purpose   : Deserializes a request
    Variables : In  - The raw data from the Connection class
                Out - The command to be performed
                Out - The deserialized object
    Returns   : 1 - Success
                0 - Fail
    ===================================================================== */
    int Deserialize(const QByteArray *, commands_t *, void *) const;

    /* =====================================================================
    Function  : Serialize
    Purpose   : Deserializes a request
    Variables : In  - The command that was performed
                In  - The object to serialize
                In  - The outcome of the operation (1 = Success, 0 = Fail)
                Out - The serialized object to send to the connection class
    Returns   : 1 - Success
                0 - Fail
    ===================================================================== */
    int Serialize(const commands_t &, void, int, QJsonObject *) const;

  private:
    void CreateContent(const QJsonObject &, void *);
    void createInvoice(const QJsonObject &, void *);
    // FIXME Change the return type to a content list
    int serializeContent(void *);
};
#endif