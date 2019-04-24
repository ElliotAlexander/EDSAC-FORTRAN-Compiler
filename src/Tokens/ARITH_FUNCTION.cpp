#include "Tokens/ARITH_FUNCTION.h"


// See superclass declaration for function definitions.
// Abstract function implemetation inherited from Token.h
std::vector<std::shared_ptr<ThreeOpCode>> ARITH_FUNCTION::generatetoc(int starting_address){

    std::vector<std::shared_ptr<ST_ENTRY> > argument_references; 

    // Assign variables, overwrite if already assigned.
    for(int argument_index = 0; argument_index < ARITH_FUNCTION::function_arguments.size(); argument_index++){
        // For each argument, assign a variable.
        Logging::logConditionalWarnMessage(SymbolTableController::getVariable(ARITH_FUNCTION::function_arguments.at(argument_index)).found, 
            "Warning - using variable name " + ARITH_FUNCTION::function_arguments.at(argument_index) + " in Arithmetic Function Call will cause the initial value of " + ARITH_FUNCTION::function_arguments.at(argument_index) + " to be overwritten.");
        Logging::logInfoMessage("Adding argument in position 1: " + ARITH_FUNCTION::function_arguments.at(argument_index));
        // Arguments are handled entirely by reference.
        argument_references.push_back(SymbolTableController::addUnDeclaredVariable(ARITH_FUNCTION::function_arguments.at(argument_index), "", ST_ENTRY_TYPE::UNASSIGNED_T));
    }

    // Generate the three op code required for the right hand side.
    // The arithmeteic parser handles this. 
    // We just need to include the three op code before calling the function
    TOC_RETURN_VALUE res = std::unique_ptr<RDParseTreeNode>(::parseADString(ARITH_FUNCTION::function_resolution))->generateThreeOPCode(starting_address);
    
    // Register the function with the function handler. 
    ::addArithmeticFunctionMapping(function_name, argument_references, res.pre_string, res.call_value);
    return {};
}

// See superclass declaration for function definitions.
// Abstract function implemetation inherited from Token.h
bool ARITH_FUNCTION::initaliseToken(std::string input){

    std::vector<std::string> equals_split;
    std::string variable_list, function_name_temp;


    /**
     *  Split the string on the equals - this gives us a defined left and right hand side.
     *  If there are more than two equals signs, the string will split into three or more. If this happens, something has gone wrong.
     **/
    boost::split(equals_split, input, boost::is_any_of("="));
    Logging::logConditionalErrorMessage((equals_split.size() > 2), "Syntax Error - found multiple equals symbols in Arithmetic Statement.");
    if(equals_split.size() != 2){
        Logging::logErrorMessage("Failed to parse arithmetic function. Multiple equals symbols inside arithmetic function {" + input + "}.");
        // If this step failed to parse, exit. Else we'll segfault later on.
        return false;
    }

    bool in_args = 0;
    /**
     * 
     * Loop through the left hand side
     * Extract the arguments and the function name.
     * We iterate from left to right. Once we're inside a the brackets, in_args is set to true.
     * 
     * Everything before the brackets is considered rthe function name, and pulled out as such.
     * Arugments are seperated by a comma, and each argument is loaded as a string into variable_list.
     * 
     * **/
    for(std::string::size_type i = 0; i < equals_split.at(0).size(); i++) {
        if(in_args == 0 && equals_split.at(0)[i] == '('){
            in_args = 1;
        } else if(in_args == 1 && equals_split.at(0)[i] == ')'){
            break;
        } else if(in_args){
            variable_list.push_back(equals_split.at(0)[i]);
        } else if(!in_args){
            function_name_temp.push_back(equals_split.at(0)[i]);
        }
    }    


    // Set the member  variable for the function name.
    ARITH_FUNCTION::function_name = function_name_temp;

    // For the argumment string, break the string down by commas.
    // seperate out each argument, append them to an internal representation.
    std::vector<std::string> var_list_temp;
    boost::split(var_list_temp, variable_list, boost::is_any_of(","));

    if(var_list_temp.size() == 0){

        // Debugging message - if the user has enabled it.
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded zero command arguments");
    } else {

        // For each argument, construct an internal representation and append it to the member variables.
        for(std::vector<std::string>::iterator it = var_list_temp.begin(); it != var_list_temp.end(); ++it){
            ARITH_FUNCTION::function_arguments.push_back(*it);

            // Inform the user of what we've loaded, if enabled.
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Function argument : " + *it);
        }
    }

    /**
     * 
     * 
     *  The right hand side of the functionn should all be one big arithmetic expression
     *  we can rely on the arithmetic parser to handle this. 
     *  Set a member variable to the string that is the right hand side. We'll process trhe right hand side as an arithmetic in GenerateTOC. 
     * */
    ARITH_FUNCTION::function_resolution = equals_split[1];

    // If the right hand side isn't found - throw an error.
    Logging::logConditionalErrorMessage((equals_split[1].length() == 0), "Failed to load right hand side string, length was zero.");
    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Function name: " + ARITH_FUNCTION::function_name);
    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Right hand side " + equals_split[1]);
    return true;
    
}

