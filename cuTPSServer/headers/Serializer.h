#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <iostream>
#include <stdexcept>

#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

#include "../common/headers/Content.h"
#include "../../common/headers/Definitions.h"

using namespace std;

class Serializer {
        public:

                /* =====================================================================
                // Function  : Deserialize
                // Purpose   : Deserializes a request
                // Variables : In  - The raw data from the Connection class
                //             Out - The deserialized object
                // Returns   : The command to be performed
                ===================================================================== */
                // Added 2 string arguments for ISBN/username and possible chapter/section #
                commands_t Deserialize(const QByteArray &, void *, string&, string&) const;

                /* =====================================================================
                // Function  : Serialize
                // Purpose   : Deserializes a request
                // Variables : In  - The command that was performed
                //             In  - The object to serialize
                //             In  - The outcome of the operation (1 = Success, 0 = Fail)
                // Returns   : The serialized object to send to the connection class
                // ===================================================================== */
            QByteArray* Serialize(const commands_t &, void *, const status_t) const;

        private:
                // This is deprecated since we changed commands_t to be more seperate i.e ADD_CHAPTER, ADD_TEXTBOOK, ADD_SECTION
                // void createContent(const QJsonObject &, void *) const;
                void createTextbook(const QJsonObject &, void *) const;
                void createChapter(const QJsonObject &, void *, string& outISBN) const;
                void createSection(const QJsonObject &, void *, string& outISBN, int chapterNo) const;

                void createInvoice(const QJsonObject &, void *) const;

                // returns an error
                // 1st Argument:
                int serializeContent(void *, QByteArray *) const;
};
#endif
