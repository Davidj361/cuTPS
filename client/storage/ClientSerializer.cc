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
    return true;
}

bool ClientSerializer::deserialize(QByteArray& inJson, QList<Course*> &courses){

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
    int i,j,k,l;
    for(i = 0; i < content.size(); i++){
        QJsonObject coursej = content.at(i).toObject();
        Course *newCourse;
        createCourse(coursej, newCourse);
        if(newCourse == NULL)
            continue;
        courses.append(newCourse);
        QJsonArray textbooks = coursej["textbooks"].toArray();
        for(j = 0; j < textbooks.size(); j++){
            QJsonObject textbookj = textbooks.at(j).toObject();
            Textbook *newTb;
            createTextbook(textbookj, newTb);
            if(newTb == NULL)
                continue;
            newCourse->addTextbook(newTb);
            QJsonArray chapters = textbookj["chapters"].toArray();
            for(k=0; k<chapters.size(); k++){
                QJsonObject chapterj = chapters.at(k).toObject();
                Chapter *newCh;
                createChapter(chapterj, newCh, newTb);
                if(newCh == NULL)
                    continue;
                newTb->addChapter(newCh);
                QJsonArray sections = chapterj["sections"].toArray();
                for(l=0; l < sections.size(); l++){
                    QJsonObject sectionj = sections.at(l).toObject();
                    Section *newSec;
                    createSection(sectionj, newSec, newCh, newTb);
                    if(newSec == NULL)
                        continue;
                    newCh->addSection(newSec);
                }
            }
        }

    }
// TODO deserialize arrays



}

void ClientSerializer::createCourse(QJsonObject &json, Course *&newCourse){
    QString courseTitle = json["courseTitle"].toString();
    QString courseCode = json["courseCode"].toString();
    QString term = json["term"].toString();
    newCourse = new Course(courseTitle, courseCode, term);
}

void ClientSerializer::createTextbook(const QJsonObject &json, Textbook *&newTextbook) const {



    QString title( json["title"].toString() );
    bool available( json["available"].toBool() );
    float price( (float)( json["price"].toDouble() ) );
    QString author( json["author"].toString() );
    QString ISBN( json["ISBN"].toString() );
    QString publisher( json["publisher"].toString() );
    QString edition( json["edition"].toString() );
    QString description( json["description"].toString() );
    int year( (int)( json["year"].toDouble() ) );

    // XXX NEW MEMORY HERE
    newTextbook = new Textbook(ISBN, title, publisher, author, year, edition, description, available, price);
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
