#include "Statement.h"

Statement::Statement(std::string statement_body, std::string label, int line_no){
    Statement::statement_body = statement_body;
    Statement::label = label;
    Statement::line_no = line_no;
    Statement::statement_body_no_ws = ::stripWhitespaceString(statement_body);
}

IDENTIFY_STATEMENT_RESULT_T Statement::identifyStatement(){


    DO* dostmt = new DO();
    SUBROUTINE* substmt = new SUBROUTINE();
    END* endstmt = new END();
    CALL* callstmt = new CALL();
    RETURN* returnstmt = new RETURN();
    ARITH_FUNCTION* arithstmt = new ARITH_FUNCTION();
    STOP* stop_stmt = new STOP();
    VAR_DECLR* var_declr = new VAR_DECLR();
    DIMENSION* dimen_stmt = new DIMENSION();
    GOTO* goto_stmt = new GOTO();
    ASSIGN* assign_stmt = new ASSIGN();
    IF* if_stmt = new IF();
    EQUIVALENCE* eq_stmt = new EQUIVALENCE();
    FORMAT* format_stmt = new FORMAT();
    PAUSE* pause_stmt = new PAUSE();
    FUNCTION_DEFINITION* function_stmt = new FUNCTION_DEFINITION();
    ASSIGNED_GOTO* assigned_goto = new ASSIGNED_GOTO();
    COMPUTED_GOTO* computed_goto = new COMPUTED_GOTO();



    // TODO - There msut be a better way to do this. 
    std::vector<Token*> tokens{
        dostmt,
        format_stmt,
        eq_stmt,
        substmt,
        endstmt,
        callstmt,
        returnstmt,
        arithstmt,
        stop_stmt,
        var_declr,
        dimen_stmt,
        goto_stmt,
        assign_stmt,
        if_stmt,
        pause_stmt,
        function_stmt,
        assigned_goto,
        computed_goto
    };
    bool found = false;


    Token* result;

    if(Globals::output_regex_matching_strings ){
        for(std::vector<std::string>::size_type i = 0; i != tokens.size(); i++){ 
            Logging::logInfoMessage("[REGEX] " + tokens[i]->getRegex());
        }
        Globals::output_regex_matching_strings = false;
    }

    // Iterate through token types.
    for(std::vector<std::string>::size_type i = 0; i != tokens.size(); i++){ 
        // Check token is valud - parse token type. 
        if(tokens[i]->isValid(statement_body_no_ws, (tokens[i]->getRegex()))){
            if(found){
                Logging::logErrorMessage("Error parsing line - line matches two possible tokens [" + std::to_string(Statement::line_no + 1) + "]{" + statement_body + "}");
                Logging::logErrorMessage("Second matching token: " + tokens[i]->getTokenName());
                continue; 
            } 
            Logging::logConditionalMessage(Globals::dump_tokens, "[" + std::to_string(Statement::line_no + 1) + "][" + tokens[i]->getTokenName() + "] { " + statement_body + " }");

            found = true;
            result = tokens[i];
            tokens[i] = nullptr;
            if(Globals::lazy_tokens){
                break;
            }
        }
    };

    if(!found){
        Logging::logErrorMessage("Cannot find valid token for line [" + std::to_string(Statement::line_no + 1) + "]{" + statement_body + "}");
        return IDENTIFY_STATEMENT_RESULT_T{nullptr, false};
    } else {
        for(int index = 0; index < tokens.size(); index++){
            delete(tokens[index]);
        }
        return IDENTIFY_STATEMENT_RESULT_T{result, true};
    }
}


std::string Statement::getStatementBody(){
    return Statement::statement_body_no_ws;
}

std::string Statement::getStatementLabel(){
    return Statement::label;
}