#include "Tokens/ASSIGNED_GOTO.h"


// See superclass declaration for function definitions.
// Abstract function implemetation inherited from Token.h
bool ASSIGNED_GOTO::initaliseToken(std::string input){
    if(input.substr(0, 4) == "GOTO"){       // The token has already been identified, so remove the keyword.
        input.erase(0,4);

        /**
         * We already know the format of the statement from the REGEX checks, so we can be confident that this shouldn't fail.
         **/
        ASSIGNED_GOTO::goto_variable = input.substr(0, input.find(',')); 
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded ASSIGNED GOTO Control Variable " + ASSIGNED_GOTO::goto_variable);
        
        /**
         * Having removed the variable value - remove it from the overall string. 
         **/
        input = input.erase(0, input.find_first_of(','));  
        input = input.erase(0, input.find('('));                

        input.pop_back(); 
        input.erase(0,1);


        // Split the string by commas, parsing each argument into the array.
        std::vector<std::string> arguments;
        boost::split(arguments, input, boost::is_any_of(","));


        // If there are no arguments - we have an error. Again, regex should catch this.
        if(arguments.size() == 0){
            // Regex should catch this, but to be safe.
            Logging::logErrorMessage("Error - failed to find any arguments inside ASSIGNED GOTO Statement list.");
            return false;
        }

        // Index is used to output to the user which argument is which, so it starts at 1.
        // this is purely cosmetic, index is not used for any backend implementation
        int index = 1;
        for(std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); ++it){

            // Each element of the arg list is an arithmetic statement.
            // The arithmetic parser handles this, store the result in a member variable. 
            ASSIGNED_GOTO::goto_arg_list.push_back(::parseADString((*it)));

            // We maintain a second list of string arguments. This helps us produce meaningful error messages later. 
            ASSIGNED_GOTO::goto_arg_list_string.push_back((*it));
            // Dump the output to the user, if enabled. Here index is used to make the output meaninful.
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded argument " + std::to_string(index) + ": " + (*it));
            index++;
        }
        // Done
        return true;
    } else {
        /**
         * This shouldn't ever happen - if it does then something is wrong with REGEX parsing.
         * This error should be caught by regex.
         **/
        Logging::logErrorMessage( "Assertation error - Failed to load ASSIGNED GOTO token.");
        printErrorLocation(0, input);
        return false;
    }
}

std::vector<std::shared_ptr<ThreeOpCode>> ASSIGNED_GOTO::generatetoc(int starting_address){
    std::vector<std::shared_ptr<ThreeOpCode> > pre_string;


    // buffer flush is used to flush any unused values into. 
    // It should never be treated as data or executed. 
	ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
	Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");


    // The main comparison variable. If this ins't declared, we have a problem.
    ALL_ST_SEARCH_RESULT goto_control = SymbolTableController::getVariable(ASSIGNED_GOTO::goto_variable);
    Logging::logConditionalErrorMessage(!goto_control.found, 
        "Failed to find ASSIGNED GOTO Control Variable. ASSIGNED GOTO Variables need to be assigned before use. This token will *not* be processed."
    );
    
    if(!goto_control.found){
        return {};
    }
    std::shared_ptr<ST_ENTRY> temp_int = SymbolTableController::addTemp(std::string("1"), ST_ENTRY_TYPE::INT_T);


    /** 
     * We iterate through each GOTO argument, comparing it to the control variable.
     * This code is generated infinitely, and rather expensive.
     * 
     * Each iteration checks another element of the assigned variables.
     * 
     **/

    // keep track of which variable we're on. - we can't use a pure iterator as we're pulling in values from different sources.
    int index = 0;
    for(std::vector<std::unique_ptr<RDParseTreeNode> >::iterator it = ASSIGNED_GOTO::goto_arg_list.begin(); it < ASSIGNED_GOTO::goto_arg_list.end(); ++it){

        // Add a line mapping - this is the 'end result' of the goto, if successful. 
        LineMapping::LineMappingReturn mapping = LineMapping::retrieveLineMapping(std::stoi(ASSIGNED_GOTO::goto_arg_list_string.at(index)));

        // This line mapping reflects a 'skip' - if the check immediately fails, skip over the rest of the checks
        // The addition of six  = the size of the added three op code. This is how far we should skip if we immedeiately fail.
        std::shared_ptr<int> negative_goto = LineMapping::addTemporaryLineMapping(starting_address + pre_string.size() + 6);
        Logging::logConditionalErrorMessage(!mapping.result, "Warning - failed to find line mapping for " + ASSIGNED_GOTO::goto_arg_list_string.at(index));

        // For clarity - pull out the value from the return value.
        std::shared_ptr<int> goto_line_mapping = mapping.value;

        // insert any required computation for the arguments to be usable.
        TOC_RETURN_VALUE toc_ret = (*it)->generateThreeOPCode(starting_address);
        pre_string.insert(pre_string.end(), toc_ret.pre_string.begin(), toc_ret.pre_string.end());

        // Clear acc
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
        
        // We check if the value two values are equal by adding one to the acc, then subtracting the other. We can then check if the accumulator is zero.
        // If it is zero, then the two values are equal.
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(goto_control.result, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(toc_ret.call_value, THREE_OP_CODE_OPERATIONS::SUBTRACT_TO_ACCUMULATOR, false)));
        
        // check for zero
        // If negative - skip
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(negative_goto, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_NEGATIVE, false)));
        // else - subtract one. If the accumulator was positive, and then became negative when we subtracted 1, then the original value must have been zero.
        // therefore the two values must be equal.
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int, THREE_OP_CODE_OPERATIONS::SUBTRACT_TO_ACCUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(goto_line_mapping, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_NEGATIVE, false)));
        // If the two values aren't equal, we can just continue with the next value.
        // the top of the loop clears the accumulator.
        index += 1;
    }

    // Return the generated three op code. 
    return pre_string;
}