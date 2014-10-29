#include "headers/Serializer.h"

using namespace std;

commands_t Serializer::deserialize(const QByteArray &in_json, void *out_object) const {

  // Create a QJsonDocument from the QByteArray
  QJsonDocument jdoc = QJsonDocument::fromJson(in_json);
  QJsonObject json;

  // Create a QJsonObject from the QJsonDocument
  if (jdoc.isNull()) {
    throw runtime_error("ERROR: Serializer::Deserialize(). Improperly formatted JSON");
  }
  else
    json = jdoc.object();

  // What command is being asked of us?
  commands_t out_command = static_cast<commands_t>( json["command"].toDouble() );

  switch (out_command) {
    case ADD_CONTENT:
      // If it's this one then we need construct a list of content
      this->createContent(json, out_object);
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
  }

  return out_command;
}

QByteArray *Serializer::serialize(const commands_t &in_command, void *in_object, bool in_outcome) const {
  QJsonObject json;
  QJsonDocument jdoc;
  QByteArray *retArray;

  json["command"] = in_command;
  json["outcome"] = in_outcome;

  if (in_command == GET_CONTENT) {
    if (!this->serializeContent(in_object, retArray))
      throw runtime_error("ERROR: Serializer::Serialize(), error while serializing an object");
  }

  // TODO - convert json object to bytearray

  return json;
}

// Construct content
void Serializer::createContent(const QJsonObject &, void *) const {
  // for this we want to create a a textbook with all its corresponding chapters and sections
  
}

// Construct Invoice
void Serializer::createInvoice(const QJsonObject &, void *) const {
}

// Create a Json array or object for all the content
int Serializer::serializeContent(void *, QByteArray *) const {
  return 0;
}
