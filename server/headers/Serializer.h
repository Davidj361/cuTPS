#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <stddef.h>
#include <string>
#include <iostream>

// #include "UI.h"
// #include "ServerFacade.h"

class Serializer {
    public:
        Serializer();
        ~Serializer();

	// public functions
        int deserialize(json*, void*);
	int serialize(int, void*, json*);
    private:
};
#endif
