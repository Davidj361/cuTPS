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
        throw std::runtime_error("ERROR: Serializer::Deserialize(). Improperly formatted JSON");
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
            (int)json["c_id"].toDouble());
}


void ServerSerializer::deserialize(QJsonObject &json, Chapter *&ch){

    Textbook *tb = new Textbook(json["isbn"].toString(),"","","",-1,"","",false, -1);
    ch = new Chapter(json["title"].toString(), (int)json["chapterNo"].toDouble(), tb, json["description"].toString(),
            json["available"].toBool(), (float)json["price"].toDouble(), (int)json["c_id"].toDouble());
}

void ServerSerializer::deserialize(QJsonObject &json, Invoice *&in){
    qDebug()<<"here";
        // TODO deserialze invoice
    QJsonArray contents = json["contents"].toArray();
    QList<int> cids;
    foreach(QJsonValue v, contents){
        cids.append((int) v.toObject()["c_id"].toDouble());
    }

    in = new Invoice(json["username"].toString(), cids);

}

void ServerSerializer::deserialize(QJsonObject &json, User*& u){
    u = new User(json["username"].toString(), json["password"].toString(), json["type"].toString(),
            json["name"].toString());
}

void ServerSerializer::deserialize(QJsonObject &json, Section *&s){
    Textbook *tb = new Textbook(json["isbn"].toString(),"","","",-1,"","",false, -1);
    Chapter *ch = new Chapter("", (int)json["chapterNo"].toDouble());
    s = new Section(json["title"].toString(), (int)json["sectionNo"].toDouble(), ch,
            tb, json["description"].toString(), json["available"].toBool(),
            (float)json["price"].toDouble(), (int)json["c_id"].toDouble());

}

void ServerSerializer::deserialize(QJsonObject& json, Class*& cl){

    QJsonObject coursej = json["course"].toObject();
    Course *course = new Course(coursej["courseCode"].toString(), coursej["courseTitle"].toString());
    cl = new Class(json["semester"].toString(), course);

    QJsonObject tbj = json["booklist"].toObject();

    cl->addTextbook(new Textbook(tbj["isbn"].toString(), tbj["title"].toString(), tbj["publisher"].toString(),
            tbj["author"].toString(), (int)tbj["year"].toDouble(), tbj["edition"].toString(),
            tbj["descrition"].toString(), tbj["available"].toBool(), (float)tbj["price"].toDouble(),
            (int)tbj["cid"].toDouble()));
}

void ServerSerializer::deserializeCourse(QJsonObject& json, Course*& c){
    c = new Course(json["courseCode"].toString(), json["courseTitle"].toString());
}



void ServerSerializer::serializeClasses(QList<Class*>& list,commands_t command, QByteArray& out){

    QJsonObject outjson;
    outjson["command"] = command;
    outjson["status"] = SUCCESS;

    QJsonArray classArr;

    foreach(Class *c, list){

        QJsonObject cjson;
        c->serialize(cjson);
        classArr.append(cjson);

    }

    outjson["classes"] = classArr;

    QJsonDocument doc(outjson);
    out = doc.toJson();


}

void ServerSerializer::serializeError(QString& error, commands_t command, QByteArray& out){
    QJsonObject json;
    json.insert("command", command);
    json.insert("status", ERROR);
    json.insert("message", error);
    QJsonDocument doc(json);
    out = doc.toJson();
}

void ServerSerializer::serializeSuccess(commands_t command, QByteArray& out ){
    QJsonObject json;
    json.insert("command", command);
    json.insert("status", SUCCESS);
    QJsonDocument doc(json);
    out = doc.toJson();
}

void ServerSerializer::serializeUser(Serializable &obj, commands_t command ,QByteArray & out){
    QJsonObject res;
    res["command"] = command;

    QJsonObject objjson;
    obj.serialize(objjson);
    res["status"] = SUCCESS;
    res["user"] = objjson;

    QJsonDocument doc(res);
    out = doc.toJson();

}

