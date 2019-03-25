#include "ProgramStructure/FunctionMapping.h"

std::map<std::string, ARITH_FUNCTION_MAPPING_ENTRY> arithmetic_function_mappings;
std::map<std::string, FUNCTION_MAPPING_ENTRY> function_mappings;
std::shared_ptr<int> return_address_mapping = std::shared_ptr<int>(new int(-1));



ARITH_FUNCTION_MAPPING_ENTRY addArithmeticFunctionMapping(std::string function_name, std::vector<std::shared_ptr<ST_ENTRY> > arguments, std::vector<std::shared_ptr<ThreeOpCode> > function_body, std::shared_ptr<ST_ENTRY> return_addr){
    std::map<std::string,ARITH_FUNCTION_MAPPING_ENTRY>::iterator it = arithmetic_function_mappings.find(function_name);
    if(it != arithmetic_function_mappings.end())
    {
        Logging::logErrorMessage("Function " + function_name + " already exists!");
        Logging::logErrorMessage("The later definition of the function will be used.");
    }

    Logging::logConditionalInfoMessage(Globals::output_function_mappings, "Adding function " + function_name + ".");
    Logging::logConditionalInfoMessage(Globals::output_function_mappings, "Function " + function_name + " has " + std::to_string(arguments.size()) + " argument(s).");

    ARITH_FUNCTION_MAPPING_ENTRY entry = {
        return_addr,
        function_body,
        arguments
    };

    arithmetic_function_mappings.insert(std::map<std::string, ARITH_FUNCTION_MAPPING_ENTRY>::value_type(function_name, entry));
    return entry;
}

ARITH_FUNCTION_MAPPING_RETURN getArithmeticFunctionMapping(std::string function_name, std::vector<std::shared_ptr<ST_ENTRY> > arguments) {
    std::vector<std::shared_ptr<ThreeOpCode> > return_arr;

    std::map<std::string,ARITH_FUNCTION_MAPPING_ENTRY>::iterator it = arithmetic_function_mappings.find(function_name);
    ARITH_FUNCTION_MAPPING_ENTRY entry;
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


bool addFunctionMapping(std::string name, std::vector<std::string> arguments, int start_line){
    std::shared_ptr<int> line_mapping = LineMapping::addTemporaryLineMapping(start_line);
    FUNCTION_MAPPING_ENTRY entry = {
        line_mapping, 
        arguments,
        FUNCTION_ENTRY_TYPE::FUNCTION_TYPE,
    };

    SymbolTableController::enterFunctionScope(name);
    function_mappings.insert(std::map<std::string, FUNCTION_MAPPING_ENTRY>::value_type(name, entry));
    Logging::logInfoMessage("Adding function mapping for function " + name);
    return true;
}


FUNCTION_MAPPING_RETURN getFunctionMapping(std::string function_name, int return_address, std::vector<std::shared_ptr<ST_ENTRY> > arguments){
    std::map<std::string, FUNCTION_MAPPING_ENTRY>::iterator it = function_mappings.begin(); it = function_mappings.find(function_name);
    FUNCTION_MAPPING_ENTRY entry;
    if( it !=function_mappings.end()){
        entry = it->second;
        if(entry.arguments.size() != arguments.size()){
            Logging::logErrorMessage("Warning - function " + function_name + " takes " + std::to_string(entry.arguments.size())  + ". Found " + std::to_string(arguments.size()));
            for(int argument_index = 0; argument_index < arguments.size(); argument_index++){
                SymbolTableController::addLinkedVariable(arguments.at(argument_index), entry.arguments.at(argument_index));
            }
            return {
                {},
                false
            };
        } else {
            SymbolTableController::enterFunctionScope(function_name);
            std::shared_ptr<int> return_address_ptr = LineMapping::addTemporaryLineMapping(return_address);
            return_address_mapping = return_address_ptr;
            std::vector<std::shared_ptr<ThreeOpCode> > return_toc;
            
            std::shared_ptr<ST_ENTRY> flush = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME).result;
            return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(std::to_string(1), THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(entry.start_line, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_POSTITIVE, false)));
            Logging::logInfoMessage("Entered function successfully.");
            return {return_toc, true};
        }
    } else {
        Logging::logErrorMessage("Failed to find function " + function_name);
        return {
            {}, 
            false
        };
    }
}

std::vector<std::shared_ptr<ThreeOpCode> > exitFunction(){
    int* compare = new int (-1);
    if(!(return_address_mapping.get() == compare)){
        std::shared_ptr<ST_ENTRY> flush = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME).result;
        std::vector<std::shared_ptr<ThreeOpCode> > return_toc;
        std::shared_ptr<ST_ENTRY> temp = SymbolTableController::addTemp("", ST_ENTRY_TYPE::UNASSIGNED_T);
        std::shared_ptr<ST_ENTRY> temp_int = SymbolTableController::addTemp("1", ST_ENTRY_TYPE::INT_T);
        return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
        return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
        return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(return_address_mapping, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_POSTITIVE, false)));
        return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
        return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
        SymbolTableController::exitFunctionScope();
        return return_toc;
    } else {
        Logging::logErrorMessage("Error - attempted to exit a function while not inside one.");
        return {};
    }
}