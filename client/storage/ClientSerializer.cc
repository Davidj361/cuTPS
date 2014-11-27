#include "ClientSerializer.h"

void ClientSerializer::serialize(Serializable &obj, commands_t command, QByteArray &request) const{
    QJsonObject json;
    json.insert("command", command);
    QJsonObject objJson;
    obj.serialize(objJson);
    json.insert("serialized", objJson);
    QJsonDocument doc(json);
    request = doc.toJson();
}

bool ClientSerializer::deserialize(QByteArray& inJson){
    // Create a QJsonDocument from the QByteArray
    QJsonDocument jdoc = QJsonDocument::fromJson(inJson);
    QJsonObject json;

    // Create a QJsonObject from the QJsonDocument
    if (jdoc.isNull())
        throw runtime_error("ERROR: Serializer::Deserialize(). Improperly formatted JSON");
    else
        json = jdoc.object();
    if(json.value("status").toDouble() != SUCCESS)
        throw runtime_error(json.value("message").toString().toStdString());
}

bool ClientSerializer::deserialize(QByteArray& inJson, QList<Textbook> textbooks, QList<Course> courses){

    // Create a QJsonDocument from the QByteArray
    QJsonDocument jdoc = QJsonDocument::fromJson(inJson);
    QJsonObject json;

    // Create a QJsonObject from the QJsonDocument
    if (jdoc.isNull())
        throw runtime_error("ERROR: Serializer::Deserialize(). Improperly formatted JSON");
    else
        json = jdoc.object();
    if(json.value("command").toDouble() != GET_CONTENT)
        throw runtime_error("Error: ClientSerializer::Deserialize(). Command not readable");
    QJsonArray content = json.value("content").toArray();
// TODO deserialize arrays



}
