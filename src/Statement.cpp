#include "Statement.h"

Statement::Statement(std::string statement_body, std::string label, int line_number){
    std::vector<Token*> tokens;
    DO dostmt;
    SUBROUTINE substmt;
    END endstmt;
    CALL callstmt;
    PROGRAM programstmt;
    RETURN returnstmt;
    ARITH_FUNCTION arithstmt;
    tokens.push_back(&dostmt);
    tokens.push_back(&substmt);
    tokens.push_back(&endstmt);
    tokens.push_back(&callstmt);
    tokens.push_back(&programstmt);
    tokens.push_back(&returnstmt);
    tokens.push_back(&arithstmt);
    bool found = false;
    for(std::vector<std::string>::size_type i = 0; i != tokens.size(); i++){ 
        if(tokens[i]->isValid(statement_body)){
            if(Globals::dump_tokens) { 
                std::cout << "[" << line_number + 1 << "][" << tokens[i]->getTokenName() << "] {" << statement_body << "\t}" << std::endl;
            }
            found = true;
        }
    };

    if(!found){
        std::cout << StringConstants::ERROR_TAG << "Cannot find valid token for line [" << line_number + 1 << "]{" << statement_body << "}" << std::endl;
    }
}