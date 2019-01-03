#ifndef __STATEMENT_H_INCLUDED
#define __STATEMENT_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>

#include "Constants.h"
#include "Globals.h"
#include "Tokens/DO.h"
#include "Tokens/SUBROUTINE.h"
#include "Tokens/END.h"
#include "Tokens/CALL.h"
#include "Tokens/RETURN.h"
#include "Tokens/ARITH_FUNCTION.h"
#include "Tokens/VAR_DECLR.h"
#include "Tokens/STOP.h"
#include "Token.h"

class Statement {
    public:
        Statement(std::string statement_body, std::string label, int line_number);
    private:
};

#endif