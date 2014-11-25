#include "ClientSerializer.h"

void ClientSerializer::Serialize(Serializable &obj, commands_t command, QJsonObject &request) const{
    request.insert("command", command);
    QJsonObject json;
    obj.serialize(json);
    request.insert("serialized", json);
}
