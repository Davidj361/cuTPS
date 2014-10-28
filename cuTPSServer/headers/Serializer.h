#ifndef SERIALIZER_H
#define SERIALIZER_H

<<<<<<< HEAD:server/headers/Serializer.h
#include <iostream>

#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

#include "headers/Definitions.h"

// #include "UI.h"
// #include "ServerFacade.h"

class Serializer {
        public:
                Serializer();
                ~Serializer();

                // TODO debate if deserialize or serialize should be const?

                // public functions
                
                // enum commands_t {ADD_CONTENT, ADD_INVOICE, GET_CONTENT};

                // TODO See if the input type should be a string or just a QJsonObject same for serialize
                // Perhaps should be given QByteArray as we are working with Qt and we are probably going to send and receive with that datatype
                
                // 1st argument: give the Json object to be deserialized
                // 2nd argument: being possible data created
                // The return type being the commands_t enum as defined in headers/Definitions.h
                commands_t deserialize(const QByteArray&, void*);

                // 1st argument: give the command on what to ask of serializer
                // 2nd argument: give successful or failure from the requested operation from deserialize
                // 3rd argument: give the content list if was requested
                // return: returned Json object to send back to client
                const QByteArray* serialize(const commands_t&, int, void* = 0);

        private:
                void createContent(const QJsonObject&, void*);
                void createInvoice(const QJsonObject&, void*);
                // FIXME Change the return type to a content list
                int serializeContent(void*);
=======
#include <string>

using namespace std;

class Serializer {
    public:
        Serializer();
        ~Serializer();

	// public functions
    int deserialize(string*, string*, void*);
    int serialize(int, void*, string*);
    private:
>>>>>>> f8c780e78b034f08413f6951af755180882b7a64:cuTPSServer/headers/Serializer.h
};
#endif
