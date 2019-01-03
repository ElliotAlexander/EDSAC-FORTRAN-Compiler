#ifndef __TOKEN_H_INCLUDED
#define __TOKEN_H_INCLUDED

#include <string>

class Token{
    public:
        virtual bool isValid(std::string input) = 0;
        virtual std::string getTokenName() = 0;
    private:
};

#endif