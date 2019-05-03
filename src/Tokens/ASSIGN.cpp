#include "Tokens/ASSIGN.h"

/**
 * 
 * 
 * These Helper functions
 * 
 **/ 
inline bool isFloat( std::string myString ) {
    std::istringstream iss(myString);
    float f;
    iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
    return iss.eof() && !iss.fail(); 
}

inline bool isInt(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

// See superclass declaration for function definitions.
// Abstract function implemetation inherited from Token.h
std::vector<std::shared_ptr<ThreeOpCode>> ASSIGN::generatetoc(int starting_address){
    /**
     * The assignment value is handled by the arithmetic parser, so the first thing we need to do is construct the assignment.
     **/
	std::vector<std::shared_ptr<ThreeOpCode> > pre_string;
	TOC_RETURN_VALUE toc_res = assignment_value->generateThreeOPCode(starting_address);


    // load the buffer flush variable
    // This variable is used as a 'waste' bin to flush any unused values into.
    // It should never be used as data, nor executed. 
    ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
    Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");


    // inform the symbol table of our new variable.
    ALL_ST_SEARCH_RESULT st_res = SymbolTableController::getVariable(ASSIGN::variable_name);

    // Add the assignment value to the output.
    pre_string.insert(pre_string.begin(), toc_res.pre_string.begin(), toc_res.pre_string.end());


    // if the variable already exists - we need to overwrite it programatically
    if(st_res.found){
        // Load the assignment variable, compute it, then transfer the value into the address of the previously mapped variable.
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Remapping variable " + ASSIGN::variable_name);
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(toc_res.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
		pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_res.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
    } else {

        // If this is the first time this variable is declared, we can just add a link from it's value to the value of the assignment variable.
        // When we request X, we'll get the address for it's linked counterpart.
        SymbolTableController::addLinkedVariable(toc_res.call_value, ASSIGN::variable_name);
    }

    return pre_string;
}

// See superclass declaration for function definitions.
// Abstract function implemetation inherited from Token.h
bool ASSIGN::initaliseToken(std::string input){
    if(input.substr(0, 6) == "ASSIGN"){
        std::string input_backup = input;
        // Strip the keyword - we've already identified the statement.
        input.erase(0,6);

        // We need ot handle this a bit differently
        // For silly reasons, ASSIGN doesn't use an equalls operator,
        // Case: what if a variable name is TOTO
        // ASSIGNTOTOTO5 would be valid.

        /**
         * 
         * Get the index of the 'TO' part of rthe assign keyword. This allows us to split the statement into two
         **/
        std::size_t found = input.find_last_of("TO");


        // Load the variable name
        std::string variable_name_temp = input.substr(0, found-1);

        // Check the validity of the variable name.
        if(variable_name_temp.length() < 1){
            Logging::logErrorMessage("Failed to parse variable name.");
            ::printErrorLocation(found-1, input);
            return false;
        }        


        // Load assignment
        std::string assignment_string_temp = std::string((input.substr(found+1, input.length())));
    
        // check it's validity
        if(assignment_string_temp.length() < 1){
            Logging::logErrorMessage("Failed to parse assignment value.");
            ::printErrorLocation(found+1, input_backup);
            return false;
        }
        


        // We can't easily check for weird arithmetic if there's a sign in the mix, so remove it. 
        // Only use this removed copy for checking that the assignment string is indeed a number
        // This is disregarded once we've checked that it' indeed an int
        std::string assigminent_string_checking = assignment_string_temp;
        if(assigminent_string_checking.at(0) == '-'){
            assigminent_string_checking.erase(0,1);
        }


        if(!(isFloat(assigminent_string_checking) && isInt(assigminent_string_checking))){
            // Due to some flexibilites in the REGEX of assign, we need to double  check the user hasn't done something like:
            // ASSIGN X TO -5-500
            // And throw an error if they have. 
            Logging::logErrorMessage("Value " + assigminent_string_checking + " could not be parsed - it is not a valid number. Arithmetic statements are not allowed in ASSIGNMENT operations.");
            return false;
        } else {
            // Assign member variables
            ASSIGN::variable_name = variable_name_temp;

            // The assignment value is handled by the arithmetic parser, and recorded as a member variable to the head of the parse tree.
            ASSIGN::assignment_value = ::parseADString(assignment_string_temp);

            // If enabled
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded variable name : " + variable_name_temp);
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded variable assignment : " + assignment_string_temp);
            return true;
        }
    } else {

        /**
         *  This should have been caught in Regex - the token shouild never have got this far without the ASSIGN keyword.
         *  If it has - something has gone seriously wrong. This check is the backup. 
         **/
        Logging::logErrorMessage( "Assertation error - failed to load ASSIGN token. ");
        printErrorLocation(0, input);
        return false;
    }
}

