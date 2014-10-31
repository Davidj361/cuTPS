#include "headers/Serializer.h"
#include "../common/headers/Textbook.h"

using namespace std;

commands_t Serializer::Deserialize(const QByteArray &in_json, void *out_object, string& str1, string& str2) const {

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
                                        this->createTextbook(json, out_object);
                                        break;
                                default:
                                        throw runtime_error("ERROR: Serializer::Deserialize(), Invalid JSON['status']");
                        }
                        break;
                        this->createContent(json, out_object);
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
                                        this->createChapter(json, out_object);
                                        break;
                                default:
                                        throw runtime_error("ERROR: Serializer::Deserialize(), Invalid JSON['status']");
                        }
                        break;
                        this->createContent(json, out_object);
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
                                        this->createSection(json, out_object);
                                        break;
                                default:
                                        throw runtime_error("ERROR: Serializer::Deserialize(), Invalid JSON['status']");
                        }
                        break;
                        this->createContent(json, out_object);
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
                                        break;
                                case ERROR:
                                        break;
                                case REQUEST:
                                        // This is the server so we need to notify controller with command_t and ask for creation of all the objects and give back the user name
                                        str1 = dynamic_cast<string>( json["username"].toString() );
                                default:
                                        throw runtime_error("ERROR: Serializer::Deserialize(), Invalid JSON['status']");
                        }
                        break;
                default:
                        throw runtime_error("ERROR: Serializer::Deserialize(), Invalid JSON['command']");
        }

        return out_command;
}

QByteArray* Serializer::Serialize(const commands_t &in_command, void *in_object, status_t status) const {
  QJsonObject json;
  QJsonDocument jdoc;
  QByteArray *retArray = new QByteArray();

  json["command"] = in_command;

  if(status == REQUEST){
    switch(in_command){
      // Call serialize on the content object and adds it to the json object.
      case ADD_CONTENT:
        json["content"] = *(static_cast<Content*>(in_object)->serialize());
        json["status"] = REQUEST;
        break;
      case ADD_INVOICE:

        // serialize
        break;
      case GET_CONTENT:
        //serialize
        break;
      default:
        //error?
        break; 
    }
  }

  // TODO - convert json object to bytearray


  return retArray;
}

void Serializer::createTextbook(const QJsonObject& json, void* retData) const {
        QJsonObject textbook = json["textbook"].toObject();

        QString title( textbook["title"].toString() );
        bool available( static_cast<bool>( textbook["available"].toDouble() ) );
        float price( static_cast<float>( textbook["price"].toDouble() ) );
        QString author( textbook["author"].toString() );
        QString ISBN( textbook["ISBN"].toString() );
        QString publisher( textbook["publisher"].toString() );
        QString edition( textbook["edition"].toString() );
        QString description( textbook["description"].toString() )
        int year( static_cast<int>( textbook["year"].toDouble() ) );

        // XXX NEW MEMORY HERE
        Textbook* pTextbook = new Textbook(title, available, price, author, ISBN, publisher, edition, description, year);
        retData = static_cast<void*>(pTextbook);
        return;
}

void Serializer::createChapter(const QJsonObject& json, void* retData, string& ISBN) const {
        QJsonObject chapter = json["chapter"].toObject();

        QString title( textbook["title"].toString() );
        bool available( static_cast<bool>( textbook["available"].toDouble() ) );
        float price( static_cast<float>( textbook["price"].toDouble() ) );
        int chapterNo( static_cast<int>( textbook["chapterNo"].toDouble() ) );
        // We need to pass back ISBN through Serializer::Deserialize
        ISBN = textbook["ISBN"].toString();

        // XXX NEW MEMORY HERE
        Chapter* pChapter = new Chapter(title, available, price, chapterNo);
        retData = static_cast<void*>(pChapter);
        return;
}

void Serializer::createSection(const QJsonObject &, void *, string& outISBN, int chapterNo) const {
        QJsonObject chapter = json["chapter"].toObject();

        QString title( textbook["title"].toString() );
        bool available( static_cast<bool>( textbook["available"].toDouble() ) );
        float price( static_cast<float>( textbook["price"].toDouble() ) );
        // We need to pass back ISBN through Serializer::Deserialize
        ISBN = textbook["ISBN"].toString();
        chapterNo static_cast<int>( textbook["chapterNo"].toDouble() );

        // XXX NEW MEMORY HERE
        Section* pSection = new Section(title, available, price);
        retData = static_cast<void*>(pSection);
        return;
}


// Construct Invoice
void Serializer::createInvoice(const QJsonObject &, void *) const {
}

// Create a Json array or object for all the content
int Serializer::serializeContent(void *, QByteArray *) const {
        return 0;
}
