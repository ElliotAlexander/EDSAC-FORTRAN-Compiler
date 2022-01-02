#include "Statement.h"


/**
 * 
 *  Class Statement:
 *  
 *  Member Variables:
 *          std::string statement_body -> 
               The body of the statement encapsulated within this class
 *          std::string statement_body_no_ws -> 
               The body of the statement with whitespace removed. 
               This is essential for matching the REGEX strings.
 *          std::string label -> 
               The label (characters 0->5) of the statement encapsulated within this class. 
               Note that the label is broken down from the body.
 *          int line_no -> 
               The line number for this statement in the input file. 
 *
 *
 *  This class encapsulates a single statement inside the program.
 *  It also provides the infastructure for identifying the type of statement, and passing
 *  the result to the relevant token.
 * 
 **/

Statement::Statement(std::string statement_body, std::string label, int line_no){
    Statement::statement_body = statement_body;
    Statement::label = label;
    Statement::line_no = line_no;
    Statement::statement_body_no_ws = ::stripWhitespaceString(statement_body);
}

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
    CONTINUE* continue_stmt = new CONTINUE();
    COMMON* common_stmt = new COMMON();           // There's an ambiguity somewhere with COMMON


    // TODO - There must be a better way to do this. 

    // Build an array of all possible Tokens. 
    // Note that this array will be cleared from the heap before the function exits.
    // Responsibility for the <single> correct token is passed ot the calling function.
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
        read_stmt,
        common_stmt,
        continue_stmt
    };


    if(Globals::output_regex_matching_strings ){        // Enabled via command line.
        for(std::vector<std::string>::size_type i = 0; i != tokens.size(); i++){ 
            Logging::logInfoMessage("[REGEX] " + tokens[i]->getRegex());
        }
        Globals::output_regex_matching_strings = false; // we only need to do this once. Disable the flag after.
    }

    // Iterate through token types.
    for(std::vector<std::string>::size_type i = 0; i != tokens.size(); i++){ 
        // If the token matches the statement body (without whitespace), we have identified the token.
        if(tokens[i]->isValid(statement_body_no_ws, (tokens[i]->getRegex()))){  
            // unless the token has already been found - this gives us a problem.
            // Inform the user, and continue optimistically.
            if(found){
                Logging::logErrorMessage("Error parsing line - line matches two possible tokens [" + 
                    std::to_string(Statement::line_no + 1) + 
                    "]{" + statement_body + "}"
                );
                Logging::logErrorMessage("Second matching token: " + tokens[i]->getTokenName());
                continue; 
            } 

            Logging::logConditionalMessage(Globals::dump_tokens, "[" + 
                std::to_string(Statement::line_no + 1) + "][" + 
                tokens[i]->getTokenName() + "] { " + 
                statement_body + " }"
            );

            found = true;                   
            result = tokens[i];             
            tokens[i] = nullptr;            
        }
    };

    if(!found){         // If the loop has finished and a token has not been found, warn the user. 
        Logging::logErrorMessage("Cannot find valid token for line [" + std::to_string(Statement::line_no + 1) + "]{" + statement_body + "}");
        // The result flag is important for informing the calling class not to touch the Token pointer.
        return IDENTIFY_STATEMENT_RESULT_T{nullptr, false};      
    } else {
        for(int index = 0; index < tokens.size(); index++){
            // If we have found the correct token, it's already been removmed from the array.
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