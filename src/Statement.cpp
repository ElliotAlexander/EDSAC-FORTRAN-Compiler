#include "Statement.h"

Statement::Statement(std::string statement_body, std::string label, int line_no){
    Statement::statement_body = statement_body;
    Statement::label = label;
    Statement::line_no = line_no;
    Statement::statement_body_nows = ::stripWhitespaceString(statement_body);
}

Token* Statement::identifyStatement(){

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
    EQUIVALENCE eq_stmt;
    FORMAT format_stmt;

    std::vector<Token*> tokens{
        &dostmt,
        &format_stmt,
        &eq_stmt,
        &substmt,
        &endstmt,
        &callstmt,
        &returnstmt,
        &arithstmt,
        &stop_stmt,
        &var_declr,
        &dimen_stmt,
        &goto_stmt,
        &assign_stmt,
        &if_stmt
    };

    Token* result;
    bool found = false;

    // Iterate through token types.
    for(std::vector<std::string>::size_type i = 0; i != tokens.size(); i++){ 
        
        // Check token is valud - parse token type. 
        if(tokens[i]->isValid(statement_body_nows, (tokens[i]->getRegex()))){

            //
            if(found){
                std::cerr << StringConstants::ERROR_TAG + "Error parsing line - line matches two possible tokens [" << Statement::line_no + 1 << "]{" << statement_body << "}" << std::endl;
                std::cerr << StringConstants::ERROR_TAG + "Second matching token: " + tokens[i]->getTokenName() << std::endl;
                continue; 
            }

            if(Globals::dump_tokens) { 
                std::cout << "[" << Statement::line_no + 1 << "][" << tokens[i]->getTokenName() << "] {" << statement_body << "\t}" << std::endl;
            }

            found = true;
            result = tokens[i];
            if(Globals::lazy_tokens){
                break;
            }
        }
    };

    if(!found){
        std::cout << StringConstants::ERROR_TAG << "Cannot find valid token for line [" << Statement::line_no + 1 << "]{" << statement_body << "}" << std::endl;
    }
    return result;
}


std::string Statement::getStatementBody(){
    return Statement::statement_body_nows;
}
