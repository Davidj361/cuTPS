#include "ServerSerializer.h"

ServerSerializer::ServerSerializer(){

}

ServerSerializer::~ServerSerializer(){}

commands_t ServerSerializer::deserialize(QByteArray & bytes, QJsonObject &json){
    // Create a QJsonDocument from the QByteArray
    QJsonDocument jdoc = QJsonDocument::fromJson(bytes);
    QJsonObject req;

    // Create a QJsonObject from the QJsonDocument
    if (jdoc.isNull())
        throw runtime_error("ERROR: Serializer::Deserialize(). Improperly formatted JSON");
    else
        req = jdoc.object();

    // What command is being asked of us?
    commands_t out_command = (commands_t) req["command"].toDouble();
    json = req["serialized"].toObject();
    return out_command;
}

void ServerSerializer::deserialize(QJsonObject &json,Textbook *&tb){
    tb = new Textbook(json["isbn"].toString(), json["title"].toString(), json["publisher"].toString(),
            json["author"].toString(), (int)json["year"].toDouble(), json["edition"].toString(),
            json["descrition"].toString(), json["available"].toBool(), (float)json["price"].toDouble(),
            (int)json["cid"].toDouble());
}


void ServerSerializer::deserialize(QJsonObject &json, Chapter *&ch){
    ch = new Chapter(json["title"].toString(), (int)json["chapterNo"].toDouble(), 0, json["description"].toString(),
            json["available"].toBool(), (float)json["price"].toDouble(), (int)json["c_id"].toDouble());
}

void ServerSerializer::deserialize(QJsonObject &json, Invoice *&in){

}

void ServerSerializer::deserialize(QJsonObject &json, Section *&s){
    s = new Section(json["title"].toString(), (int)json["sectionNo"].toDouble(), 0,
            0, json["description"].toString(), json["available"].toBool(),
            (float)json["price"].toDouble(), (int)json["c_id"].toDouble());

}
