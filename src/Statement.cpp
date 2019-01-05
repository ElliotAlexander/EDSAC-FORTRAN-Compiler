#include "Statement.h"

Statement::Statement(std::string statement_body, std::string label, int line_number){
    std::vector<Token*> tokens;
    DO dostmt;
    SUBROUTINE substmt;
    END endstmt;
    CALL callstmt;
    RETURN returnstmt;
    ARITH_FUNCTION arithstmt;
    STOP stop_stmt;
    VAR_DECLR var_declr;
    DIMENSION dimen_stmt;
    GOTO goto_stmt;
    ASSIGN assign_stmt;
    IF if_stmt;
    tokens.push_back(&dostmt);
    tokens.push_back(&substmt);
    tokens.push_back(&endstmt);
    tokens.push_back(&callstmt);
    tokens.push_back(&returnstmt);
    tokens.push_back(&arithstmt);
    tokens.push_back(&stop_stmt);
    tokens.push_back(&var_declr);
    tokens.push_back(&dimen_stmt);
    tokens.push_back(&goto_stmt);
    tokens.push_back(&assign_stmt);
    tokens.push_back(&if_stmt);
    
    bool found = false;
    for(std::vector<std::string>::size_type i = 0; i != tokens.size(); i++){ 
        if(tokens[i]->isValid(statement_body, (tokens[i]->getRegex()))){
            if(found){
                std::cerr << StringConstants::ERROR_TAG + "Error parsing line [" << line_number + 1 << "]{" << statement_body << "}" << std::endl;
                continue; 
            }

            if(Globals::dump_tokens) { 
                std::cout << "[" << line_number + 1 << "][" << tokens[i]->getTokenName() << "] {" << statement_body << "\t}" << std::endl;
            }

            found = true;
            if(Globals::lazy_tokens){
                break;
            }
        }
    };

    if(!found){
        std::cout << StringConstants::ERROR_TAG << "Cannot find valid token for line [" << line_number + 1 << "]{" << statement_body << "}" << std::endl;
    }
}