#include "ProgramStructure/FunctionMapping.h"


FUNCTION_MAPPING_ENTRY addArithmeticFunctionMapping(std::string function_name, std::vector<std::shared_ptr<ST_ENTRY> > arguments, std::vector<std::shared_ptr<ThreeOpCode> > function_body, std::shared_ptr<ST_ENTRY> return_addr){
    std::map<std::string,FUNCTION_MAPPING_ENTRY>::iterator it = arithmetic_function_mappings.find(function_name);
    if(it != arithmetic_function_mappings.end())
    {
        Logging::logErrorMessage("Function " + function_name + " already exists!");
        Logging::logErrorMessage("The later definition of the function will be used.");
    }

    Logging::logConditionalInfoMessage(Globals::output_function_mappings, "Adding function " + function_name + ".");
    Logging::logConditionalInfoMessage(Globals::output_function_mappings, "Function " + function_name + " has " + std::to_string(arguments.size()) + " argument(s).");

    FUNCTION_MAPPING_ENTRY entry = {
        return_addr,
        function_body,
        arguments
    };

    arithmetic_function_mappings.insert(std::map<std::string, FUNCTION_MAPPING_ENTRY>::value_type(function_name, entry));
    return entry;
}

FUNCTION_MAPPING_RETURN getArithmeticFunctionMapping(std::string function_name, std::vector<std::shared_ptr<ST_ENTRY> > arguments) {
    std::vector<std::shared_ptr<ThreeOpCode> > return_arr;

    std::map<std::string,FUNCTION_MAPPING_ENTRY>::iterator it = arithmetic_function_mappings.find(function_name);
    FUNCTION_MAPPING_ENTRY entry;
    Logging::logConditionalInfoMessage(Globals::output_function_mappings, "Calling function " + function_name + ".");
    if(it != arithmetic_function_mappings.end())
    {
        entry = it->second;
        if(entry.arguments.size() != arguments.size()){
            Logging::logWarnMessage("Warning - found " + std::to_string(arguments.size()) + " arguments for function " + function_name + ", expected " + std::to_string(entry.arguments.size()));
        }


        for(int argument_index = 0; argument_index < entry.arguments.size(); argument_index++){

            // Add argument to accumulator.
            return_arr.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arguments.at(argument_index), THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            // Assign argument from accumulator.
            return_arr.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(entry.arguments.at(argument_index), THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
        }

        return_arr.insert(return_arr.end(), entry.function_body.begin(), entry.function_body.end());
        return {true, return_arr, entry.value_return_address};
    };

    Logging::logErrorMessage("Function " + function_name + " not found!");
    return {false, {}};
}   