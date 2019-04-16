#include "Statement.h"


// Statement::Statement(std::string statement_body, std::string label, int line_no)
//
// @param std::string statement_body -> The complete statement, with whitespace, without a label or continuation bit.
// @param std::string label -> the statement line label
// @param int line_no -> The statement line_number, as it was in the input file. This is used mainly for error messages.
//
// Note that Statement contains the member variable statement_body_no_ws, which is the statemebnt bodoy minus the (irrelevant) whitespace.
//
// This class acts as the main point of identifying statements. 
//
//
Statement::Statement(std::string statement_body, std::string label, int line_no){
    Statement::statement_body = statement_body;
    Statement::label = label;
    Statement::line_no = line_no;
    Statement::statement_body_no_ws = ::stripWhitespaceString(statement_body);
}


// IDENTIFY_STATEMENT_RESULT_T Statement::identifyStatement()
// 
// @return IDENTIFY_STATEMENT_RESULT_T -> A boolean indicating whether the statement was identified, and a pointer to the token object for that Statement.
//
// This function takes the body of the statement, and validates it against a list of possible tokens.
// Once the correct token is found, it is removed from the list, and the list cleared. A pointer to the correct token is then
// returned. The calling class then becomes responsible for that token. 
//
// Each token is identified by comparing it's associated REGEX string with the statement body.
// If the string is a match, then token object is initialised. 
// 
//
IDENTIFY_STATEMENT_RESULT_T Statement::identifyStatement(){
    bool found = false;
    Token* result;
    
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
    PRINT* print_stmt = new PRINT();
    READ* read_stmt = new READ();


    // TODO - There msut be a better way to do this. 

    // Build an array of all possible Tokens. 
    // Note taht this array will be cleared from the heap before the function exits.
    // Responsibility for the <single> correct token is passed ot the calling function.
    // 
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
        computed_goto,
        print_stmt,
        read_stmt
    };


    if(Globals::output_regex_matching_strings ){        // Enabled via command line.
        for(std::vector<std::string>::size_type i = 0; i != tokens.size(); i++){ 
            Logging::logInfoMessage("[REGEX] " + tokens[i]->getRegex());
        }
        Globals::output_regex_matching_strings = false; // we only need to do this once. Disable the flag after.
    }

    // Iterate through token types.
    for(std::vector<std::string>::size_type i = 0; i != tokens.size(); i++){ 
        if(tokens[i]->isValid(statement_body_no_ws, (tokens[i]->getRegex()))){  // If the token matches the statement body (without whitespace), we have identified the token.
            // unless the token has already been found - this gives us a problem.
            // Inform the user, and continue optimistically.
            if(found){
                Logging::logErrorMessage("Error parsing line - line matches two possible tokens [" + std::to_string(Statement::line_no + 1) + "]{" + statement_body + "}");
                Logging::logErrorMessage("Second matching token: " + tokens[i]->getTokenName());
                continue; 
            } 

            Logging::logConditionalMessage(Globals::dump_tokens, "[" + std::to_string(Statement::line_no + 1) + "][" + tokens[i]->getTokenName() + "] { " + statement_body + " }");

            found = true;                   // Once we've seen a token, set this flag. If we see another token that matches, warn the user.
            result = tokens[i];             // Set the result. Note that if two tokemns are found (are more), the last one will be used.
            tokens[i] = nullptr;            // Dereference the pointer in the array.
            if(Globals::lazy_tokens){       // If this is enabled, break once we've found a single valid token.
                break;                      // 
            }
        }
    };

    if(!found){         // If the loop has finished and a token has not been found, warn the user. 
        Logging::logErrorMessage("Cannot find valid token for line [" + std::to_string(Statement::line_no + 1) + "]{" + statement_body + "}");
        return IDENTIFY_STATEMENT_RESULT_T{nullptr, false};      // The result flag is important for informing the calling class not to touch the Token pointer.
    } else {
        for(int index = 0; index < tokens.size(); index++){
            delete(tokens[index]);                              // If we have found the correct token, it's already been removmed from the array.
        }                                                       //  Hence, clear the array, free the heap.
        return IDENTIFY_STATEMENT_RESULT_T{result, true};       // return
    }
}


std::string Statement::getStatementBody(){
    return Statement::statement_body_no_ws;
}

std::string Statement::getStatementLabel(){
    return Statement::label;
}