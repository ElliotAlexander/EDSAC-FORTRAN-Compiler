#include "ProgramStructure/FunctionMapping.h"

std::map<std::string, ARITH_FUNCTION_MAPPING_ENTRY> arithmetic_function_mappings;
std::map<std::string, SUBROUTINE_MAPPING_ENTRY> subroutine_mappings;
std::map<std::string, FUNCTION_MAPPING_ENTRY> function_mappings;


std::shared_ptr<int> return_address_mapping = std::shared_ptr<int>(new int(-1));


std::pair<std::shared_ptr<int>, std::shared_ptr<int>> SUBROUTINE_MAPPING_PAIR;
std::pair<std::shared_ptr<int>, std::shared_ptr<int>> FUNCTION_MAPPING_PAIR;

std::string current_function_name;
bool inside_function_flag;

std::shared_ptr<int> addSubroutineMapping(std::string name, std::vector<std::string> arguments, int start_line){
    SUBROUTINE_MAPPING_PAIR.first = LineMapping::addTemporaryLineMapping(start_line);
    SUBROUTINE_MAPPING_PAIR.second = LineMapping::addTemporaryLineMapping(start_line);

    SUBROUTINE_MAPPING_ENTRY entry = { SUBROUTINE_MAPPING_PAIR.first, arguments };
    SymbolTableController::enterFunctionScope(name);
    for(int index = 0; index < arguments.size(); index++){
        SymbolTableController::addDeclaredVariable(arguments.at(index), "", ST_ENTRY_TYPE::UNASSIGNED_T);
    }
    subroutine_mappings.insert(std::map<std::string, SUBROUTINE_MAPPING_ENTRY>::value_type(name, entry));
    return SUBROUTINE_MAPPING_PAIR.second;
}

SUBROUTINE_MAPPING_RETURN getSubroutineMapping(std::string subroutine_name, int return_address, std::vector<std::shared_ptr<ST_ENTRY> > arguments){
    std::map<std::string, SUBROUTINE_MAPPING_ENTRY>::iterator it = subroutine_mappings.begin(); it = subroutine_mappings.find(subroutine_name);
    if( it != subroutine_mappings.end()){
        SUBROUTINE_MAPPING_ENTRY entry = it->second;
        if(entry.arguments.size() != arguments.size()){
            Logging::logErrorMessage("Warning - Subroutine " + subroutine_name + " takes " + std::to_string(entry.arguments.size())  + ". Found " + std::to_string(arguments.size()));
            return {{}, false};
        } else {
            SymbolTableController::enterFunctionScope(subroutine_name);
            std::vector<std::shared_ptr<ThreeOpCode> > return_toc;
            return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("0", THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            
            for(int index = 0; index < entry.arguments.size(); index++){
                return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arguments.at(index), THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
                ALL_ST_SEARCH_RESULT arg_var = SymbolTableController::getVariable(entry.arguments.at(index));
                return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg_var.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            }

            std::shared_ptr<int> return_address_mapping = LineMapping::addTemporaryLineMapping(return_address + return_toc.size());


            return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(return_address_mapping, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(entry.start_line, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_NEGATIVE, false)));
            return {return_toc, true};
        }
    } else {
        Logging::logErrorMessage("Failed to find function " + subroutine_name);
        return {
            {}, 
            false
        };
    }
}

std::vector<std::shared_ptr<ThreeOpCode> > exitSubroutine(int end_line){
    if(true){
        std::vector<std::shared_ptr<ThreeOpCode> > return_toc = {            // This is to be overwritten!!!
                std::shared_ptr<ThreeOpCode>(new ThreeOpCode("", THREE_OP_CODE_OPERATIONS::STOP_PROGRAM, false))
        };
        std::shared_ptr<ST_ENTRY> flush = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME).result;
        std::shared_ptr<ST_ENTRY> result = SymbolTableController::addTemp("", ST_ENTRY_TYPE::UNASSIGNED_T);
        SymbolTableController::exitFunctionScope();
        *SUBROUTINE_MAPPING_PAIR.second = end_line + 1;
        return return_toc;
    } else {
        Logging::logErrorMessage("Error - attempted to exit a Subroutine Program while not inside one.");
        return {

        };
    }
}

std::shared_ptr<int> addFunctionMapping(std::string name, std::vector<std::string> arguments, int start_line){
    FUNCTION_MAPPING_PAIR.first = LineMapping::addTemporaryLineMapping(start_line);
    FUNCTION_MAPPING_PAIR.second = LineMapping::addTemporaryLineMapping(start_line);
    SymbolTableController::enterFunctionScope(name);
    std::shared_ptr<ST_ENTRY> return_val = SymbolTableController::addTemp("", ST_ENTRY_TYPE::UNASSIGNED_T);

    FUNCTION_MAPPING_ENTRY entry = { FUNCTION_MAPPING_PAIR.first, arguments, return_val };
    for(int index = 0; index < arguments.size(); index++){
        SymbolTableController::addDeclaredVariable(arguments.at(index), "", ST_ENTRY_TYPE::UNASSIGNED_T);
    }

    current_function_name = name;
    inside_function_flag = true;
    Logging::logInfoMessage("Entering function " + current_function_name);
    function_mappings.insert(std::map<std::string, FUNCTION_MAPPING_ENTRY>::value_type(name, entry));
    return FUNCTION_MAPPING_PAIR.second;
}


FUNCTION_MAPPING_RETURN getFunctionMapping(std::string function_name, std::vector<std::shared_ptr<ST_ENTRY> > arguments, int return_address) {
    if(inside_function_flag){
        Logging::logErrorMessage("Function " + function_name + " is nested inside " + current_function_name);
        return {};
    }

    std::map<std::string, FUNCTION_MAPPING_ENTRY>::iterator it = function_mappings.begin(); it = function_mappings.find(function_name);
    if( it != function_mappings.end()){
        FUNCTION_MAPPING_ENTRY entry = it->second;
        if(entry.arguments.size() != arguments.size()){
            Logging::logErrorMessage("Warning - Function " + function_name + " takes " + std::to_string(entry.arguments.size())  + ". Found " + std::to_string(arguments.size()));
            return {false, {}, {}};
        } else {

            if(!entry.return_val_set){
                Logging::logErrorMessage("Error - return value for function " + function_name + " is not set.");
                return {false, {}, {}};
            }

            SymbolTableController::enterFunctionScope(function_name);
            std::vector<std::shared_ptr<ThreeOpCode> > return_toc;
            return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("0", THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            
            for(int index = 0; index < entry.arguments.size(); index++){
                return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arguments.at(index), THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
                ALL_ST_SEARCH_RESULT arg_var = SymbolTableController::getVariable(entry.arguments.at(index));
                return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg_var.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            }

            std::shared_ptr<int> return_address_mapping = LineMapping::addTemporaryLineMapping(return_address + return_toc.size());

            return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(return_address_mapping, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(entry.start_line, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_NEGATIVE, false)));
            return {true, return_toc, entry.return_val};
        }
    } else {
        Logging::logErrorMessage("Failed to find function " + function_name);
        return {
            false, 
            {},
            {}
        };
    }
}


FUNCTION_EXIT_RETURN exitFunction(std::string return_value, int end_line) {
    if(inside_function_flag){
        std::shared_ptr<ST_ENTRY> flush = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME).result;
        std::shared_ptr<ST_ENTRY> result = SymbolTableController::addTemp("", ST_ENTRY_TYPE::UNASSIGNED_T);
        ALL_ST_SEARCH_RESULT return_val = SymbolTableController::getVariable(return_value);
        


        if(!return_val.found){
            Logging::logErrorMessage("Return value " + return_value + " was not found inside Function Scope.");
            return {};
        }

        std::vector<std::shared_ptr<ThreeOpCode> > return_toc = {            // This is to be overwritten!!!
                std::shared_ptr<ThreeOpCode>(new ThreeOpCode("", THREE_OP_CODE_OPERATIONS::STOP_PROGRAM, false))
        };

        std::map<std::string, FUNCTION_MAPPING_ENTRY>::iterator it = function_mappings.begin(); it = function_mappings.find(current_function_name);
        if( it != function_mappings.end()){
            (*it).second.return_val = return_val.result;
            (*it).second.return_val_set = true;
        } else {
            Logging::logErrorMessage("Failed to find function entry for  " + current_function_name);
            return {};
        }

        Logging::logMessage("Exiting function");
        inside_function_flag = false;
        current_function_name = {};
        
        SymbolTableController::exitFunctionScope();
        *FUNCTION_MAPPING_PAIR.second = end_line;
        return { return_toc };
    } else {
        Logging::logErrorMessage("Error - attempted to exit a Function  while not inside one.");
        return {};
    }
}


FUNCTION_EXIT_RETURN exitFunction(std::shared_ptr<ST_ENTRY> return_value, int end_line) {
    if(inside_function_flag){
        std::shared_ptr<ST_ENTRY> flush = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME).result;
        std::shared_ptr<ST_ENTRY> result = SymbolTableController::addTemp("", ST_ENTRY_TYPE::UNASSIGNED_T);        

        std::vector<std::shared_ptr<ThreeOpCode> > return_toc = {            // This is to be overwritten!!!
                std::shared_ptr<ThreeOpCode>(new ThreeOpCode("", THREE_OP_CODE_OPERATIONS::STOP_PROGRAM, false))
        };

        std::map<std::string, FUNCTION_MAPPING_ENTRY>::iterator it = function_mappings.begin(); it = function_mappings.find(current_function_name);
        if( it != function_mappings.end()){
            (*it).second.return_val = return_value;
            (*it).second.return_val_set = true;
        } else {
            Logging::logErrorMessage("Failed to find function entry for  " + current_function_name);
            return {};
        }
        inside_function_flag = false;
        current_function_name = {};
        
        SymbolTableController::exitFunctionScope();
        *FUNCTION_MAPPING_PAIR.second = end_line;
        return { return_toc };
    } else {
        Logging::logErrorMessage("Error - attempted to exit a Function  while not inside one.");
        return {};
    }
}