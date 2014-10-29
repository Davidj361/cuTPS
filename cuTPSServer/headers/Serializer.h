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

    /* =====================================================================
    // Function  : Deserialize
    // Purpose   : Deserializes a request
    // Variables : In  - The raw data from the Connection class
    // Out - The command to be performed
    // Out - The deserialized object
    // FIXME
    //                  ***** Returns   : 1 - Success
    //                  *** 0 - Fail
    ===================================================================== */
    commands_t deserialize(const QByteArray &, void *) const;

    /* =====================================================================
    // Function  : Serialize
    // Purpose   : Deserializes a request
    // Variables : In  - The command that was performed
    // In  - The object to serialize
    // In  - The outcome of the operation (1 = Success, 0 = Fail)
    // Out - The serialized object to send to the connection class
    // Returns   : 1 - Success
    // 0 - Fail
    // ===================================================================== */
    QByteArray *serialize(const commands_t &, void *, bool) const;

  private:
    void createContent(const QJsonObject &, void *) const;
    void createInvoice(const QJsonObject &, void *) const;
    // returns an error
    // 1st Argument:
    int serializeContent(QByteArray *, void *);
};
#endif
