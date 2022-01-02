#include "Tokens/COMPUTED_GOTO.h"

bool COMPUTED_GOTO::initaliseToken(std::string input){
    if(input.substr(0, 4) == "GOTO"){
        input.erase(0,4);

        /**
         * This string is handled from the back, given GOTO (10, 15, 20), X
         * Find the variable after the last comma.
         * Once we've got the variable, we can set this to a class member.
         * This is only handled as a string. 
         **/ 
        COMPUTED_GOTO::goto_variable = input.substr(input.find_last_of(','), input.size());
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded ASSIGNED GOTO Control Variable " + COMPUTED_GOTO::goto_variable);

        // Strip the leading bracket
        goto_variable.erase(0, 1);

        // Strip the final control variable - it's already extracted.
        // We now have something in the form: (10, 15, 20)
        input = input.erase(input.find_last_of(','), input.size());
        
        // Strip the string before the brackets - this is designed to remove whitesapce.
        input.erase(0, input.find_first_of('('));

        // Remove the last bracket.
        input.pop_back();
        input.erase(0,1);

        Logging::logInfoMessage("Loaded argument string " + input);

        std::vector<std::string> arguments;
        boost::split(arguments, input, boost::is_any_of(","));


        // Error checking. Defensive programming. 
        if(arguments.size() == 0){
            // Regex should catch this, but to be safe.
            Logging::logErrorMessage("Error - failed to find any arguments inside ASSIGNED GOTO Statement list.");
            return false;
        }

        int index = 1;
        for(std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); ++it){
            COMPUTED_GOTO::goto_arg_list.push_back(::parseADString((*it)));
            COMPUTED_GOTO::goto_arg_list_string.push_back((*it));
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded argument " + std::to_string(index) + ": " + (*it));
            index++;
        }
        return true;
    } else {
        Logging::logErrorMessage( "Failed to load ASSIGNED GOTO token - couldn't parse GOTO keyword.");
        printErrorLocation(0, input);
        return false;
    }
}

std::vector<std::shared_ptr<ThreeOpCode>> COMPUTED_GOTO::generatetoc(int starting_address){
    std::vector<std::shared_ptr<ThreeOpCode> > pre_string;

    // This variable is where each unused accumulator clear will be dumped to
	ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
	Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");

    ALL_ST_SEARCH_RESULT goto_control = SymbolTableController::getVariable(COMPUTED_GOTO::goto_variable);
    Logging::logConditionalErrorMessage(!goto_control.found, "Failed to find ASSIGNED GOTO Control Variable. ASSIGNED GOTO Variables need to be assigned before use. This token will *not* be processed.");
    if(!goto_control.found){
        return {};
    }

    
    int index = 0;
    std::shared_ptr<ST_ENTRY> temp_int = SymbolTableController::addTemp(std::string("1"), ST_ENTRY_TYPE::INT_T);

    /**
     * Thus is used as a rolling trakc of index.
     * This is the variable we will manipulate to compare each assigned variable too
     * 
     **/ 
    std::shared_ptr<ST_ENTRY> index_st = SymbolTableController::addTemp("1", ST_ENTRY_TYPE::INT_T);


    // Iterate through each bracketed argument. Compare the index of each one to x. If X == the index of a line label, jump to that line label.
    for(std::vector<std::unique_ptr<RDParseTreeNode> >::iterator it = COMPUTED_GOTO::goto_arg_list.begin(); it < COMPUTED_GOTO::goto_arg_list.end(); ++it){


        /**
         *  Get the line mapping in question for each bracketted int
         *  The line mapping might exist, but not have been seen yet.
         *  Hence, throw only a warning.
         **/ 
        LineMapping::LineMappingReturn mapping = LineMapping::retrieveLineMapping(std::stoi(COMPUTED_GOTO::goto_arg_list_string.at(index)));
        Logging::logConditionalErrorMessage(!mapping.result, "Warning - Failed to load line mapping for " + COMPUTED_GOTO::goto_arg_list_string.at(index));


        // Add a line mapping for easy reference.
        std::shared_ptr<int> goto_line_mapping = mapping.value;
    

        /**
         * Generate the three op code for each argument
         **/

        TOC_RETURN_VALUE toc_ret = (*it)->generateThreeOPCode(starting_address);

        // add it to the output string
        pre_string.insert(pre_string.end(), toc_ret.pre_string.begin(), toc_ret.pre_string.end());

        // This mapping is the next value - this is where we will jump to if the values arent equal.
        std::shared_ptr<int> negative_mapping = LineMapping::addTemporaryLineMapping(pre_string.size() + starting_address + 6);

        /**
         * 
         * For instruction, add it to the accumulator, then subtract the index. If the value is negative then jump out. If the value is still positive, subtract one.
         * If the value theme becomes negative, we know that X == index. Hence, we can jump to the defined jump point..
         * 
         **/ 
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(goto_control.result, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(index_st, THREE_OP_CODE_OPERATIONS::SUBTRACT_TO_ACCUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(negative_mapping, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_NEGATIVE, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int, THREE_OP_CODE_OPERATIONS::SUBTRACT_TO_ACCUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(goto_line_mapping, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_NEGATIVE, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(index_st, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(index_st, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACCUMULATOR_NO_CLEAR, false)));

        // iterate through this process for each defined variable. 
        index += 1;
    }
    return pre_string;
}