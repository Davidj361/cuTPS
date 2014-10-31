#include "headers/Serializer.h"

using namespace std;

commands_t Serializer::Deserialize(const QByteArray &in_json, void *&out_object, QString& str1, QString& str2) const {

        // Create a QJsonDocument from the QByteArray
        QJsonDocument jdoc = QJsonDocument::fromJson(in_json);
        QJsonObject json;

        // Create a QJsonObject from the QJsonDocument
        if (jdoc.isNull())
                throw runtime_error("ERROR: Serializer::Deserialize(). Improperly formatted JSON");
        else
                json = jdoc.object();

        // What command is being asked of us?
        commands_t out_command = static_cast<commands_t>( json["command"].toDouble() );
        status_t status = static_cast<status_t>( json["status"].toDouble() );

        switch (out_command) {
                case ADD_TEXTBOOK:
                        // If it's server then we need construct a list of content
                        // As for client we just see if it was a success or error
                        switch (status) {
                                case SUCCESS:
                                        qDebug() << "ADD_TEXTBOOK was a success";
                                        break;
                                case ERROR:
                                        qDebug() << "ADD_TEXTBOOK was an error";
                                        break;
                                case REQUEST:
                                        createTextbook(json, out_object);
                                        break;
                                default:
                                        throw runtime_error("ERROR: Serializer::Deserialize(), Invalid JSON['status']");
                        }
                        break;
                case ADD_CHAPTER:
                        // If it's server then we need construct a list of content
                        // As for client we just see if it was a success or error
                        switch (status) {
                                case SUCCESS:
                                        qDebug() << "ADD_CHAPTER was a success";
                                        break;
                                case ERROR:
                                        qDebug() << "ADD_CHAPTER was an error";
                                        break;
                                case REQUEST:
                                        this->createChapter(json, out_object, str1);
                                        break;
                                default:
                                        throw runtime_error("ERROR: Serializer::Deserialize(), Invalid JSON['status']");
                        }
                        break;
                case ADD_SECTION:
                        // If it's server then we need construct a list of content
                        // As for client we just see if it was a success or error
                        switch (status) {
                                case SUCCESS:
                                        qDebug() << "ADD_SECTION was a success";
                                        break;
                                case ERROR:
                                        qDebug() << "ADD_SECTION was an error";
                                        break;
                                case REQUEST:
                                        this->createSection(json, out_object, str1, str2);
                                        break;
                                default:
                                        throw runtime_error("ERROR: Serializer::Deserialize(), Invalid JSON['status']");
                        }
                        break;
                case ADD_INVOICE:
                        // if it's server then we need to construct an invoice object
                        // As for client we just see if it was a success or error
                        switch (status) {
                                case SUCCESS:
                                        qDebug() << "ADD_INVOICE was a success";
                                        break;
                                case ERROR:
                                        qDebug() << "ADD_INVOICE was an error";
                                        break;
                                case REQUEST:
                                        this->createInvoice(json, out_object);
                                        break;
                                default:
                                        throw runtime_error("ERROR: Serializer::Deserialize(), Invalid JSON['status']");
                        }
                        break;
                case GET_CONTENT:
                        // This one will cause a problem if serializer is being client or server
                        // So we will use enum status_t
                        switch (status) {
                                // SUCCESS and ERROR are for the client
                                case SUCCESS:
                                        // Success for obtaining a content list for the client, we need to create all the textbooks, section, chapters
                                        break;
                                case ERROR:
                                        break;
                                case REQUEST:
                                        // This is the server so we need to notify controller with command_t and ask for creation of all the objects and give back the user name
                                        str1 = json["username"].toString();
                                default:
                                        throw runtime_error("ERROR: Serializer::Deserialize(), Invalid JSON['status']");
                        }
                        break;
                default:
                        throw runtime_error("ERROR: Serializer::Deserialize(), Invalid JSON['command']");
        }

        return out_command;
}

void Serializer::Serialize(const commands_t &in_command, void *in_object, status_t status, QByteArray &out) const {
  QJsonObject json;
  QJsonObject inJson;

  json["command"] = in_command;

  if(status == REQUEST){
    switch(in_command){
      // Call serialize on the content object and adds it to the json object.
      case ADD_TEXTBOOK:
      case ADD_CHAPTER:
      case ADD_SECTION:
        static_cast<Content*>(in_object)->serialize(inJson);
        json["content"] = inJson;
        break;
      case ADD_INVOICE:
        static_cast<Invoice*>(in_object)->serialize(inJson);
        json["invoice"] = inJson;
        break;
      case GET_CONTENT:
        json["username"] = static_cast<User*>(in_object)->getUserName();
        break;
      default:
        //error?
        break;
    }
    json["status"] = REQUEST;
  }
  else{
    switch(in_command){
      case GET_CONTENT:
        if(status == SUCCESS)
          serializeContent(in_object, json);
        break;
      default:
        // ?
        break;

    }
    json["status"] = status;
  }
  

  // TODO - convert json object to bytearray

  QJsonDocument jdoc(json);
  out = jdoc.toJson();
}

void Serializer::serializeContent(void* in_object, QJsonObject& json) const{

    //
    vector<Textbook*> *tbs = static_cast<vector<Textbook*>*>(in_object);
    QJsonArray tbarray;

    for(vector<Textbook*>::const_iterator iter= tbs->begin(); iter != tbs->end(); ++iter){

      QJsonObject serializedTB;
      (*iter)->serialize(serializedTB);

      vector<Chapter*> chapters = (*iter)->getChapters();
      QJsonArray chaparray;

      for(vector<Chapter*>::const_iterator chapIter= chapters.begin(); chapIter != chapters.end(); ++chapIter){

        QJsonObject serializedCh;
        (*chapIter)->serialize(serializedCh);

        vector<Section*> sections = (*chapIter)->getSections();
        QJsonArray secarray;

        for(vector<Section*>::const_iterator secIter = sections.begin(); secIter != sections.end(); ++secIter){

            QJsonObject serializedSec;
            (*secIter)->serialize(serializedSec);
            secarray.append(serializedSec);
        }

        serializedCh["sections"] = secarray;
        chaparray.append(serializedCh);

      }
      serializedTB["chapters"] = chaparray;
      tbarray.append(serializedTB);


    }
}

void Serializer::createTextbook(const QJsonObject& json, void*& retData) const {
        QJsonObject textbook = json["content"].toObject();

        QString title( textbook["title"].toString() );
        bool available( static_cast<bool>( textbook["available"].toDouble() ) );
        float price( static_cast<float>( textbook["price"].toDouble() ) );
        QString author( textbook["author"].toString() );
        QString ISBN( textbook["ISBN"].toString() );
        QString publisher( textbook["publisher"].toString() );
        QString edition( textbook["edition"].toString() );
        QString description( textbook["description"].toString() );
        int year( static_cast<int>( textbook["year"].toDouble() ) );

        // XXX NEW MEMORY HERE
        Textbook* pTextbook = new Textbook(ISBN, title, publisher, author, year, edition, description, available, price);
        if (retData != 0)
                throw runtime_error("Serializer::createTextbook, void* retData was not set null beforehand");
        else {
                retData = pTextbook;
        }
}

void Serializer::createChapter(const QJsonObject& json, void*& retData, QString& ISBN) const {
        QJsonObject chapter = json["content"].toObject();

        QString title( chapter["title"].toString() );
        bool available( static_cast<bool>( chapter["available"].toDouble() ) );
        float price( static_cast<float>( chapter["price"].toDouble() ) );
        int chapterNo( static_cast<int>( chapter["chapterNo"].toDouble() ) );
        QString description( chapter["description"].toString() );
        // We need to pass back ISBN through Serializer::Deserialize
        ISBN = chapter["ISBN"].toString();

        // XXX NEW MEMORY HERE
        Chapter* pChapter = new Chapter(title, chapterNo, 0, description, available, price);
        if (retData != 0)
                throw runtime_error("Serializer::createChapter, void* retData was not set null beforehand");
        else
                retData = static_cast<void*>(pChapter);
        return;
}

void Serializer::createSection(const QJsonObject& json, void*& retData, QString& outISBN, QString& outChapterNo) const {
        QJsonObject section = json["content"].toObject();

        QString title( section["title"].toString() );
        bool available( static_cast<bool>( section["available"].toDouble() ) );
        float price( static_cast<float>( section["price"].toDouble() ) );
        int sectionNo( static_cast<int>( section["chapterNo"].toDouble() ) );
        QString description( section["description"].toString() );
        // We need to pass back ISBN through Serializer::Deserialize
        outISBN = section["ISBN"].toString();
        outChapterNo = section["chapterNo"].toString();

        // XXX NEW MEMORY HERE
        Section* pSection = new Section(title, sectionNo, 0, 0, description, available, price);
        if (retData != 0)
                throw runtime_error("Serializer::createSection, void* retData was not set null beforehand");
        else
                retData = static_cast<void*>(pSection);
        return;
}


// Construct Invoice
void Serializer::createInvoice(const QJsonObject& json, void *& retData) const {
        // For this one we will want to createn invoice object with the username to pass back to the controller
        QJsonObject invoice = json["invoice"].toObject();
        Invoice* pInvoice = new Invoice(invoice["username"].toString());
        QJsonArray arr = invoice["contents"].toArray();

        // We iterate through arr and add each content id via Invoice::add(int);
        QJsonObject temp;
        for (QJsonArray::iterator iter = arr.begin(); iter != arr.end(); ++iter) {
                temp = (*iter).toObject();
                pInvoice->addContent( static_cast<int>(temp["cid"].toDouble() ) );
        }

        if (retData != 0)
                throw runtime_error("Serializer::createSection, void* retData was not set null beforehand");
        else
                retData = static_cast<void*>(pInvoice);
        return;
}

void Serializer::createContent(const QJsonObject& json, vector<Textbook*>& textbooks) const {
        // Check if textbooks is empty if not then throw an error
        if (!textbooks.empty())
                throw runtime_error("Serializer::createContent, vector<Textbook>& textbooks is not empty");
        // For this we will have 3 levels of arrays, top level is textbooks, 2nd is chapters, 3rd is sections
        QJsonArray content = json["content"].toArray();

        // TODO Make an overloaded function to deal with these garbage holders
        QString str1, str2;

        for (QJsonArray::const_iterator book = content.begin(); book != content.end(); ++book) {
                // We are at a textbook so we create a textbook with all the attributes then proceed to add the corresponding chapters
                Textbook* pTextbook;
                void* temp;
                this->createTextbook((*book).toObject(), temp);
                pTextbook = static_cast<Textbook*>(temp);
                QJsonArray chapters = (*book).toObject()["chapters"].toArray();

                for (QJsonArray::const_iterator chapter = chapters.begin(); chapter != chapters.end(); ++chapter) {
                        Chapter* pChapter;
                        this->createChapter((*chapter).toObject(), temp, str1);
                        pChapter = static_cast<Chapter*>(temp);
                        QJsonArray sections = (*chapter).toObject()["chapters"].toArray();

                        for (QJsonArray::const_iterator section = sections.begin(); section != sections.end(); ++section) {
                                Section* pSection;
                                this->createSection((*section).toObject(), temp, str1, str2);
                                pSection = static_cast<Section*>(temp);
                                pChapter->getSections().push_back(pSection);
                        }
                       pTextbook->getChapters().push_back(pChapter);
                }
                textbooks.push_back(pTextbook);
        }
}

