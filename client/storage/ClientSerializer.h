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

        void deserialize(QByteArray&);
        void deserialize(QByteArray&, QList<Class*>&);
        void deserialize(QByteArray&, User&);

    private:

        void createCourse(QJsonObject &, Course *&);
        void createTextbook(const QJsonObject &, Textbook *&) const;
        void createChapter(QJsonObject &, Chapter *&, Textbook*&);
        void createSection(const QJsonObject &json, Section *&newSection, Chapter *&parentCh, Textbook *&parentTb);
};
#endif

