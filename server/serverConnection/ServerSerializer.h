#ifndef SERVERSERIALIZER_H
#define SERVERSERIALIZER_H

#include <unistd.h>
#include <stdexcept>

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include "../../common/headers/Definitions.h"
#include "../../common/headers/Section.h"
#include "../../common/headers/Chapter.h"
#include "../../common/headers/Textbook.h"
#include "../../common/headers/Invoice.h"
#include "../../common/headers/Course.h"
#include "../../common/headers/Class.h"
#include "../../common/headers/Serializable.h"

class ServerSerializer : public QObject {

    public:
        ServerSerializer();
        ~ServerSerializer();

        commands_t deserialize(QByteArray &, QJsonObject&);
        void deserialize(QJsonObject&, Textbook*&);
        void deserialize(QJsonObject&, Chapter*&);
        void deserialize(QJsonObject&, Invoice*&);
        void deserialize(QJsonObject&, Section*&);
        void deserialize(QJsonObject&, User*&);
        void deserialize(QJsonObject&, Class*&);
        void deserializeCourse(QJsonObject&, Course*&);

        void serializeClasses(QList<Class*>&,commands_t command, QByteArray&);
        void serializeError(QString&, commands_t, QByteArray&);
        void serializeSuccess(commands_t command, QByteArray& out );
        void serializeUser(Serializable&,commands_t, QByteArray&);


    private:

};

#endif
