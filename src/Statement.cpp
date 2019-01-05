#include "Statement.h"

Statement::Statement(std::string statement_body, std::string label, int line_no){
    Statement::statement_body = statement_body;
    Statement::label = label;
    Statement::line_no = line_no;
    Statement::statement_body_nows = ::stripWhitespaceString(statement_body);
}

Token* Statement::identifyStatement(){
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
    EQUIVALENCE eq_stmt;
    FORMAT format_stmt;
    tokens.push_back(&dostmt);
    tokens.push_back(&format_stmt);
    tokens.push_back(&eq_stmt);
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
    Token* result;
    
    bool found = false;
    for(std::vector<std::string>::size_type i = 0; i != tokens.size(); i++){ 
        if(tokens[i]->isValid(statement_body_nows, (tokens[i]->getRegex()))){

            if(found){
                std::cerr << StringConstants::ERROR_TAG + "Error parsing line - line matches two possible tokens [" << Statement::line_no + 1 << "]{" << statement_body << "}" << std::endl;
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


bool Statement::tokenizeStatement(Token* token_type){
    token_type->tokenize(Statement::statement_body_nows);
}
