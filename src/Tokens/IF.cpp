#include "Tokens/IF.h"
// TODO save the full string to a class member, improve output.
bool IF::initaliseToken(std::string input){
    if(!(input.substr(0,2) == "IF")){
        Logging::logErrorMessage("Syntax Error - Failed to parse IF Statement. ");
        Logging::logErrorMessage("Full statement: { " + input + "}. ");
    } else {
        input.erase(input.find("IF"), 2);
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded IF String: " + input);
    }
    
    if(!parseConditionalArgument(input)){
        return false;
    }

    if(!parseRightHandSideArguments(input.substr(input.find_last_of(')') + 1, input.size()))){
        return false;
    }
    
    return true;
}

bool IF::parseConditionalArgument(std::string conditional_string_input){
    conditional_string_input = conditional_string_input.erase(0, conditional_string_input.find_first_of('('));
    conditional_string_input = conditional_string_input.erase(conditional_string_input.find_last_of(')'), conditional_string_input.size());
    
    conditional_string_input.erase(0,1);
    conditional_variable = ::parseADString(conditional_string_input);
    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Parsed conditional value succcessfully: " + conditional_string_input);
    return true;
}

bool IF::parseRightHandSideArguments(std::string rhs_input_string){
    // Breakup string by commas. 
    std::vector<std::string> instruction_values_arr;
    boost::split(instruction_values_arr, rhs_input_string, boost::is_any_of(","));
    // Iterate through: x,x,x, and so on.
    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded right hand side string " + rhs_input_string);
    if(instruction_values_arr.size() > 0){
        if(instruction_values_arr.size() > 3){
            Logging::logErrorMessage( "Found too many instructions in IF statement. Expected 3, found " + std::to_string(instruction_values_arr.size()));
            Logging::logErrorMessage("Full statement: { " + rhs_input_string + " }.");    
            return false;
        } else if(instruction_values_arr.size() < 3){
            Logging::logErrorMessage("Found too few instructions in IF statement. Expected 3, found " + std::to_string(instruction_values_arr.size()));
            Logging::logErrorMessage("Full statement: { " + rhs_input_string + " }.");
            return false;
        } else {
            int index = instruction_values_arr.size();
            for(int i = 0; i < index; i++){
                instruction_values.push_back(std::stoi(instruction_values_arr.at(i)));
                Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded instruction [" + std::to_string(i) + "]:" + instruction_values_arr.at(i));
            }
            return true;
        }
        return false;
    } else {
        Logging::logErrorMessage("Syntax Error - IF Statement instruction values are improperly formatted.");
        Logging::logErrorMessage("Expected format is: \nIF (<Conditional>) <Line label>, <Line label> [,<Line label>]");
        return false;
    }
}

std::vector<std::shared_ptr<ThreeOpCode>> IF::generatetoc(int starting_address)
{
    std::vector<std::shared_ptr<ThreeOpCode>> pre_string;

    // Get a reference to buffer flush
    ALL_ST_SEARCH_RESULT flush_to = ::getVariable(Globals::BUFFER_FLUSH_NAME);
    Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");

    TOC_RETURN_VALUE toc_ret = IF::conditional_variable->generateThreeOPCode();

    pre_string.insert(pre_string.end(), toc_ret.pre_string.begin(), toc_ret.pre_string.end());
    std::vector<std::shared_ptr<int>> arguments_computed;

    for (std::vector<int>::iterator it = instruction_values.begin(); it != instruction_values.end(); ++it)
    {
        arguments_computed.push_back(LineMapping::retrieveLineMapping((*it)));
    }

    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(toc_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arguments_computed.at(0), THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_NEGATIVE, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arguments_computed.at(2), THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_POSTITIVE, false)));
    std::shared_ptr<ST_ENTRY> temp_integer = ::addTemp("1", ST_ENTRY_TYPE::INT_T);
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_integer, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arguments_computed.at(1), THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_POSTITIVE, false)));
    return pre_string;
}