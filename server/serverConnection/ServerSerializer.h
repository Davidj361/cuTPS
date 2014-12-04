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
#include "../../common/headers/Serializable.h"

using namespace std;

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

        void serialize(QList<Course>&,commands_t command, QByteArray&);
        void serialize(QString&,commands_t, QByteArray&);
        void serializeUser(Serializable&,commands_t, QByteArray&);


    private:

};

#endif
