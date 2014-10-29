#include "headers/Serializer.h"

using namespace std;

commands_t Serializer::Deserialize(const QByteArray *in_json, void *out_object) {

  // Create a QJsonDocument from the QByteArray
  QJsonDocument jdoc = QJsonDocument::fromJson(in_json);
  QJsonObject json;

  // Create a QJsonObject from the QJsonDocument
  if (jdoc.isNull()) {
    throw runtime_error("ERROR: Serializer::Deserialize(). Improperly formatted JSON");
    return 0;
  }
  else
    json = jdoc.object();

  // What command is being asked of us?
  commands_t out_command = static_cast<commands_t>( json["command"].toDouble() );

  switch (out_command) {
    case ADD_CONTENT:
      // If it's this one then we need construct a list of content
      this->CreateContent(json, out_object);
      break;
    case ADD_INVOICE:
      // if it's this one then we need to construct an invoice
      this->createInvoice(json, out_object);
      break;
    case GET_CONTENT:
      // if it's this one then we merely do nothing else and pass off the return value
      break;
    default:
      throw runtime_error("ERROR: Serializer::Deserialize(), Invalid JSON['command']");
      return 0;
  }

  return out_command;
}

QByteArray *Serializer::Serialize(const commands_t *in_command, void *in_object, bool in_outcome) {
  QJsonObject json;
  QJsonDocument jdoc;

  json["command"] = *in_command;
  json["outcome"] = *in_outcome;

  if (*in_command == GET_CONTENT)
    if (!json["contentList"] = this->SerializeContent(in_object))
      throw runtime_error("ERROR: Serializer::Serialize(), error while serializing an object");

  // Todo - convert json object to bytearray

  return json;
}

// Construct content
void Serializer::createContent(const QJsonObject &, void *) {
}

// Construct Invoice
void Serializer::createInvoice(const QJsonObject &, void *) {
}

// Create a Json array or object for all the content
int Serializer::serializeContent(void *) {
  return 0;
}