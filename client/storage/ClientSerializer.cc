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

// Deserializing update response. Expecting only a result, no object
void ClientSerializer::deserialize(QByteArray& inJson){
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


void ClientSerializer::deserialize(QByteArray& inJson, QList<Class*> &courses){

    // Create a QJsonDocument from the QByteArray
    QJsonDocument jdoc = QJsonDocument::fromJson(inJson);
    QJsonObject json;

    // Create a QJsonObject from the QJsonDocument
    if (jdoc.isNull())
        throw runtime_error("ERROR: Serializer::Deserialize(). Improperly formatted JSON");

    json = jdoc.object();

    if(json.value("command").toDouble() != GET_CONTENT)
        throw runtime_error("Error: ClientSerializer::Deserialize(). Command not readable");

    if(json.value("status").toDouble() != SUCCESS)
        throw runtime_error(json.value("message").toString().toStdString());

    QJsonArray classesJsonArray = json.value("classes").toArray();
    foreach (const QJsonValue & classJsonValue, classesJsonArray) {
        QJsonObject classJsonObject = classJsonValue.toObject();

        Course *course = new Course(classJsonObject["code"].toString(), classJsonObject["title"].toString());
        Class *clss = new Class(classJsonObject["semester"].toString(), course);

        QJsonArray booklistJsonArray = classJsonObject.value("booklist").toArray();
        foreach (const QJsonValue & bookJsonValue, booklistJsonArray) {
            QJsonObject bookJsonObject = bookJsonValue.toObject();

            Textbook *textbook;
            createTextbook(bookJsonObject, textbook);
            clss->addTextbook(textbook);

            QJsonArray chaptersJsonArray = bookJsonObject.value("chapters").toArray();
            foreach (const QJsonValue & chaptersJsonObject, chaptersJsonArray) {
                QJsonObject chapterJsonObject = chaptersJsonObject.toObject();

                Chapter *chapter;
                createChapter(chapterJsonObject, chapter, textbook);
                textbook->addChapter(chapter);

                QJsonArray sectionsJsonArray = chapterJsonObject.value("sections").toArray();
                foreach (const QJsonValue & sectionsJsonValue, sectionsJsonArray) {
                    QJsonObject sectionJsonObject = sectionsJsonValue.toObject();

                    Section *section;
                    createSection(sectionJsonObject, section, chapter, textbook);
                }
            }
        }
    }
}

void ClientSerializer::deserialize(QByteArray& inJson, User & user) {
    // Create a QJsonDocument from the QByteArray
    QJsonDocument jdoc = QJsonDocument::fromJson(inJson);
    QJsonObject json;

    // Create a QJsonObject from the QJsonDocument
    if (jdoc.isNull())
        throw runtime_error("ERROR: Serializer::Deserialize(). Improperly formatted JSON");
    else
        json = jdoc.object();
    if(json.value("command").toDouble() != LOGIN)
        throw runtime_error("Error: ClientSerializer::Deserialize(). Command not readable");

    if (json.value("status").toDouble() != SUCCESS)
        throw runtime_error(json.value("message").toString().toStdString());

    QJsonObject userObj = json["user"].toObject();

    user.setType(userObj["type"].toString());
}

void ClientSerializer::createCourse(QJsonObject &json, Course *&newCourse) {
    QString courseTitle = json["courseTitle"].toString();
    QString courseCode = json["courseCode"].toString();
    QString term = json["term"].toString();
    // newCourse = new Course(courseTitle, courseCode, term);
}

void ClientSerializer::createTextbook(const QJsonObject &bookJsonObject, Textbook *&textbook) const {
    textbook = new Textbook(
            bookJsonObject["isbn"].toString(),
            bookJsonObject["title"].toString(),
            bookJsonObject["publisher"].toString(),
            bookJsonObject["author"].toString(),
      (int) bookJsonObject["year"].toDouble(),
            bookJsonObject["edition"].toString(),
            bookJsonObject["description"].toString(),
            bookJsonObject["available"].toBool(),
     (bool) bookJsonObject["price"].toDouble()
    );
}

void ClientSerializer::createChapter(QJsonObject &json, Chapter *&newChapter, Textbook *&parentTb){

    QString title = json["title"].toString();
    bool available = json["available"].toBool();
    float price = (float)( json["price"].toDouble() );
    int chapterNo = (int)( json["chapterNo"].toDouble() );
    QString description = json["description"].toString();
    int cid = (int) json["c_id"].toDouble();

    // XXX NEW MEMORY HERE
    newChapter = new Chapter(title, chapterNo, parentTb, description, available, price, cid);

}


void ClientSerializer::createSection(const QJsonObject &json, Section *&newSection, Chapter *&parentCh, Textbook *&parentTb){

    QString title( json["title"].toString() );
    bool available( json["available"].toBool() );
    float price( (float)( json["price"].toDouble() ) );
    int sectionNo( (int)( json["sectionNo"].toDouble() ) );
    QString description( json["description"].toString() );
    int cid = (int) json["c_id"].toDouble();

    // XXX NEW MEMORY HERE
    newSection = new Section(title, sectionNo, parentCh, parentTb, description, available, price, cid);

}
