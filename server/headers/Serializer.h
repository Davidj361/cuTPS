#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>

using namespace std;

class Serializer {
    public:
        Serializer();
        ~Serializer();

	// public functions
    int deserialize(string*, void*);
    int serialize(int, void*, string*);
    private:
};
#endif
