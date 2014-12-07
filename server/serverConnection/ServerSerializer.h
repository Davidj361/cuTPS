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

        /* =========================================================================
        Function  : deserialize
        Purpose   : Deserialize the incomming QByteArray into the command
                    into the command and json it contains
        Variables : IN  -  QByteArray containing request from client
                    OUT -  QJsonObject that has the serialized data
        Returns   : what the client wants to do
        =========================================================================== */
        commands_t deserialize(QByteArray &, QJsonObject&);

        /* =========================================================================
        Function  : deserialize
        Purpose   : Turn the deserialized json into an object
        Variables : IN  -  QJsonObject containing the serialized object
                    OUT -  object that was serialized
        Returns   : void
        =========================================================================== */
        void deserialize(QJsonObject&, Textbook*&);
        void deserialize(QJsonObject&, Chapter*&);
        void deserialize(QJsonObject&, Invoice*&);
        void deserialize(QJsonObject&, Section*&);
        void deserialize(QJsonObject&, User*&);
        void deserialize(QJsonObject&, Class*&);
        void deserializeCourse(QJsonObject&, Course*&);

        /* =========================================================================
        Function  : serializeClasses
        Purpose   : serialize the list of classes to be sent to client
        Variables : IN  -  QList of classes to be sent
                    IN  -  command contained in the request
                    OUT -  QByteArray containing serialized message
        Returns   : void
        =========================================================================== */
        void serializeClasses(QList<Class*>&,commands_t command, QByteArray&);

        /* =========================================================================
        Function  : serializeError
        Purpose   : serialize an error that was caught
        Variables : IN  -  QString containing error message
                    IN  -  command contained in the request that caused the error
                    OUT -  QByteArray containing serialized message
        Returns   : void
        =========================================================================== */
        void serializeError(QString&, commands_t, QByteArray&);

        /* =========================================================================
        Function  : serializeSuccess
        Purpose   : serialize a success message to send back to client
        Variables : IN  -  command contained in the request that caused the error
                    OUT -  QByteArray containing serialized message
        Returns   : void
        =========================================================================== */
        void serializeSuccess(commands_t command, QByteArray& out );

        /* =========================================================================
        Function  : serializeUser
        Purpose   : serialize a user object
        Variables : IN  -  serializable user
                    IN  -  command sent by client
                    OUT -  QByteArray containing serialized message
        Returns   : void
        =========================================================================== */
        void serializeUser(Serializable&,commands_t, QByteArray&);


    private:

};

#endif
