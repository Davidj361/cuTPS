#ifndef CLIENTSERIALIZER_H
#define CLIENTSERIALIZER_H

#include <iostream>
#include <stdexcept>
#include <iterator>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QString>
#include <QDebug>

#include "../../common/headers/Definitions.h"
#include "../../common/headers/Class.h"
#include "../../common/headers/Textbook.h"
#include "../../common/headers/Course.h"
#include "../../common/headers/Invoice.h"
#include "../../common/headers/Serializable.h"

using namespace std;

class ClientSerializer {
    public:

        /* =====================================================================
        // Function  : Deserialize
        // Purpose   : Deserializes a request
        // Variables : In  - The raw data from the Connection class
        //             Out - The deserialized object
        // Returns   : The command to be performed
        ===================================================================== */
        // Added 2 string arguments for ISBN/username and possible chapter/section #

        //commands_t Deserialize(const QByteArray &, void *&, QString &, QString &) const;

        /* =====================================================================
        // Function  : Serialize
        // Purpose   : Deserializes a request
        // Variables : In  - The command that was performed
        //             In  - The object to serialize
        //             In  - The outcome of the operation (1 = Success, 0 = Fail)
        // Returns   : The serialized object to send to the connection class
        // ===================================================================== */
        void serialize(Serializable&, commands_t, QByteArray&) const;

        bool deserialize(QByteArray&);
        bool deserialize(QByteArray&, QList<Class*>&);
        bool deserialize(QByteArray&, User **);

    private:

        void createCourse(QJsonObject &, Course *&);
        void createTextbook(const QJsonObject &, Textbook *&) const;
        void createChapter(QJsonObject &, Chapter *&, Textbook*&);
        void createSection(const QJsonObject &json, Section *&newSection, Chapter *&parentCh, Textbook *&parentTb);
        // This is deprecated since we changed commands_t to be more seperate i.e ADD_CHAPTER, ADD_TEXTBOOK, ADD_SECTION
        // void createContent(const QJsonObject &, void *) const;

        /* =====================================================================
        // Function  : createTextbook
        // Purpose   : To construct and allocate a textbok object and pass it off to the controller on server
        // Variables : In  - The raw data from the connection class
        //             Out - The textbook object
        // Returns   : Nothing
        // ===================================================================== */
        //void createTextbook(const QJsonObject &, void *&) const;

        /* =====================================================================
        // Function  : createChapter
        // Purpose   : To construct and allocate a chapter object and pass it off to the controller on server.
        //             To pass out the ISBN to the controller on the server.
        // Variables : In  - The raw data from the connection class
        //             Out - The textbook object
        //             Out - The ISBN for the chapter
        // Returns   : Nothing
        // ===================================================================== */
        //void createChapter(const QJsonObject &, void *&, QString *outISBN = 0) const;

        /* =====================================================================
        // Function  : createSection
        // Purpose   : To construct and allocate a chapter object and pass it off to the controller on server.
        //             To pass out the ISBN to the controller on the server.
        //             To pass out the chapter number to the controller on the server.
        // Variables : In  - The raw data from the connection class
        //             Out - The textbook object
        //             Out - The ISBN for the chapter
        //             Out - The ISBN for the chapter
        // Returns   : Nothing
        // ===================================================================== */
        //void createSection(const QJsonObject &, void *&, QString *outISBN = 0, QString *chapterNo = 0) const;

        //void createInvoice(const QJsonObject &, void *&) const;

        //void createContent(const QJsonObject &, void *&) const;

        // returns an error
        // 1st Argument:
        //void serializeContent(void *, QJsonObject &) const;
};
#endif

