#include "Tokens/COMPUTED_GOTO.h"

bool COMPUTED_GOTO::initaliseToken(std::string input){
    if(input.substr(0, 4) == "GOTO"){
        input.erase(0,4);


        COMPUTED_GOTO::goto_variable = input.substr(input.find_last_of(','), input.size());
        goto_variable.erase(0, 1);


        input = input.erase(input.find_last_of(','), input.size());
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded ASSIGNED GOTO Control Variable " + COMPUTED_GOTO::goto_variable);
        
        
        input.erase(0, input.find_first_of('('));
        input.pop_back();
        input.erase(0,1);

        Logging::logInfoMessage("Loaded argument string " + input);


        std::vector<std::string> arguments;
        boost::split(arguments, input, boost::is_any_of(","));

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

	ALL_ST_SEARCH_RESULT flush_to = ::getVariable(Globals::BUFFER_FLUSH_NAME);
	Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");

    ALL_ST_SEARCH_RESULT goto_control = ::getVariable(COMPUTED_GOTO::goto_variable);
    Logging::logConditionalErrorMessage(!goto_control.found, "Failed to find ASSIGNED GOTO Control Variable. ASSIGNED GOTO Variables need to be assigned before use. This token will *not* be processed.");
    
    // We can't generate our toc without this
    if(!goto_control.found){
        return {};
    }


    int index = 0;
    std::shared_ptr<ST_ENTRY> index_st = ::addTemp("1", ST_ENTRY_TYPE::INT_T);
    std::shared_ptr<ST_ENTRY> temp_int = ::addTemp(std::string("1"), ST_ENTRY_TYPE::INT_T);
    for(std::vector<std::unique_ptr<RDParseTreeNode> >::iterator it = COMPUTED_GOTO::goto_arg_list.begin(); it < COMPUTED_GOTO::goto_arg_list.end(); ++it){

        std::shared_ptr<int> goto_line_mapping = LineMapping::retrieveLineMapping(std::stoi(COMPUTED_GOTO::goto_arg_list_string.at(index)));
    

        TOC_RETURN_VALUE toc_ret = (*it)->generateThreeOPCode();
        pre_string.insert(pre_string.end(), toc_ret.pre_string.begin(), toc_ret.pre_string.end());

        // Clear acc
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
        // add to acc
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(goto_control.result, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
        // subtract from acc
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(index_st, THREE_OP_CODE_OPERATIONS::SUBTRACT_TO_ACCUMULATOR, false)));
        // check for zero
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(std::to_string(pre_string.size() + starting_address + 4), THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_POSTITIVE, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(std::to_string(pre_string.size() + starting_address + 3), THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_NEGATIVE, false)));
        // Ensure that the accumulator is positive
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(index_st, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(goto_line_mapping, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_POSTITIVE, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(index_st, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(index_st, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACCUMULATOR_NO_CLEAR, false)));
        index += 1;
    }
    return pre_string;
}