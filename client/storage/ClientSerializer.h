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
           Function  : Serialize
           Purpose   : serializes a request into a byte array
           Variables : In  -  A serializable object
                       In  -  The the command for the server
                       In  -  A QByteArray containing the message
           Returns   : void
          ===================================================================== */
        void serialize(Serializable&, commands_t, QByteArray&) const;

        /* =====================================================================
           Function  : deserialize
           Purpose   : deserialize a success message
           Variables : In  -  a message success or fail
           Returns   : void if success, throws exception if fail
          ===================================================================== */
        void deserialize(QByteArray&);

        /* =====================================================================
           Function  : deserialize
           Purpose   : deserialize a list of classes
           Variables : In  -  the message
                       Out -  a list of classes
           Returns   : void
          ===================================================================== */
        void deserialize(QByteArray&, QList<Class*>&);

        /* =====================================================================
           Function  : deserialize
           Purpose   : deserialize a user
           Variables : In  -  the message
                       Out -  user
           Returns   : void
          ===================================================================== */
        void deserialize(QByteArray&, User&);

    private:

        void createTextbook(const QJsonObject &, Textbook *&) const;
        void createChapter(QJsonObject &, Chapter *&, Textbook*&);
        void createSection(const QJsonObject &json, Section *&newSection, Chapter *&parentCh, Textbook *&parentTb);
};
#endif

