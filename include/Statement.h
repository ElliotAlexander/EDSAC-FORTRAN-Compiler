#ifndef __STATEMENT_H_INCLUDED
#define __STATEMENT_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>

#include "Constants.h"
#include "Tokens/DO.h"
#include "Tokens/SUBROUTINE.h"
#include "Token.h"

class Statement {
    public:
        Statement(std::string statement_body, std::string label, int line_number);
    private:
};

#endif