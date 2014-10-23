#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
    public:
        virtual ~User();
        virtual void SetUserName(string);
        virtual string GetUserName();
    private:
        string username;
};
#endif