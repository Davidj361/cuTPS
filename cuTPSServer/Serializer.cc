#include "headers/Serializer.h"

#include <stdexcept>

// For this we will have to work with JSONs
commands_t Serializer::deserialize(const QByteArray& inJson, void* retData) {
        // for reference
        // enum commands_t {ADD_CONTENT, ADD_INVOICE, GET_CONTENT};

        // Create a QJsonDocument from the QByteArray
        QJsonDocument jdoc = QJsonDocument::fromJson(inJson);
        QJsonObject json;
        if (jdoc.isNull()) {
                // TODO Add better logging
                std::cout << "ERROR: deserialize()::Serializer.cc, parsed Json is invalid!!!" << std::endl;
                return ERROR;
        }
        else
                json = jdoc.object();

        // What command is being asked of us?
        // works json["command"].toString();
        commands_t retCommand = static_cast<commands_t>( json["command"].toDouble() );

        // enum commands_t {ADD_CONTENT, ADD_INVOICE, GET_CONTENT};
        switch (retCommand) {
                case ADD_CONTENT:
                        // if it's this one then we need construct a list of content
                        this->createContent(json, retData);
                        break;
                case ADD_INVOICE:
                        // if it's this one then we need to construct an invoice
                        this->createInvoice(json, retData);
                        break;
                case GET_CONTENT:
                        // if it's this one then we merely do nothing else and pass off the return value
                        break;
                default:
                        // TODO Add proper logging
                        std::cout << "ERROR: deserialize()::Serializer.cc, didn't get proper value for json[\"command\"]" << std::endl;
                        return ERROR;
        }

        return retCommand;
}

// We will create a QJsonObject with given data
const QByteArray* Serializer::serialize(const commands_t& command, int errorState, void* contentList) {
        // we initialize an empty QJsonObject
        // XXX NEW MEMORY HERE
        QByteArray* retJson = new QByteArray();
        QJsonObject json;

        // TODO decide on the Json key names with the team
        // For the first 2, we just return a Json to indicate a success or failure for the client
        switch (command) {
                case ADD_CONTENT:
                        json["command"] = command;
                        json["error"] = errorState;
                        break;
                case ADD_INVOICE:
                        json["command"] = command;
                        json["error"] = errorState;
                        break;
                case GET_CONTENT:
                        json["command"] = command;
                        json["error"] = errorState;
                        // TODO Discuss how serializing a list of content should work along with what it actually contains
                        json["contentList"] = this->serializeContent(contentList);
                        break;
                default:
                        // TODO Add proper logging
                        std::cout << "ERROR: serialize()::Serializer.cc, didn't get proper value for command argument" << std::endl;
                        throw std::runtime_error("ERROR: serialize()::Serializer.cc, didn't get proper value for command argument");
                        return retJson;
        }
        return retJson;
}

// Construct content
void Serializer::createContent(const QJsonObject&, void*) {
}

// Construct Invoice
void Serializer::createInvoice(const QJsonObject&, void*) {
}

// Create a Json array or object for all the content
int Serializer::serializeContent(void*) {
        return 0;
}




















