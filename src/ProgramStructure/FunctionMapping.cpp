#include "ProgramStructure/FunctionMapping.h"

/**
 * 
 * Function, Subroutines and arithmetic functions are all handled differently. 
 * 
 * Each subroutine or function has a containing object, which is mapped by the name of the function or subroutine.
 * most of this class is accessors and additions for Subroutines, Functions and Arithmetic Fucntions.
 * 
 **/ 
std::map<std::string, ARITH_FUNCTION_MAPPING_ENTRY> arithmetic_function_mappings;
std::map<std::string, SUBROUTINE_MAPPING_ENTRY> subroutine_mappings;
std::map<std::string, FUNCTION_MAPPING_ENTRY> function_mappings;

/**
 * 
 * When we jump into a subroutine, this value is set.
 * If we try to jump into a function while this method is still set, then nested functions are detected.
 *  
 * Once the subroutine or function is left, this value is reset to -1.
 * 
 **/ 
std::shared_ptr<int> return_address_mapping = std::shared_ptr<int>(new int(-1));


/**
 * 
 * These mappings represent the return value of a function. 
 * 
 * i.e. this is where we should jump back to once we've finished executing the subroutine. 
 * This class is responsible for managing the return location.
 * 
 * 
 * Subroutines and functions are jumped into at the top level. Proceeding tokens are processed as normal.
 * 
 * 
 * Once a return statement is seen, this value is accessed, a return instruction constructed, and program flow trannsferred 
 * back out of the function or subroutine.
 * 
 **/ 
std::pair<std::shared_ptr<int>, std::shared_ptr<int>> SUBROUTINE_MAPPING_PAIR;
std::pair<std::shared_ptr<int>, std::shared_ptr<int>> FUNCTION_MAPPING_PAIR;



/**\
 * 
 * 
 * These variables function in a similar manner to the above pairs.
 * They are used as a simpler flag - are we in a subroutine or function, what is it's name.
 * This is mainly used for detecting nested functions and outputting useful error messages.
 * 
 **/ 
std::string current_function_name;
bool inside_function_flag;

std::string current_subroutine_name;
bool inside_subroutine_flag;


/**
 * 
 * std::shared_ptr<int> addSubroutineMapping(std::string name, std::vector<std::string> arguments, int start_line)
 * 
 * this function is called from a Subroutine token.
 * Tjhe subroutine is added, and a temporary value for the return address is set.
 * The name of arguments is provided, this allows variables to be declared for the function inside the function scope.
 * 
 * A new symbol table is configured for the subroutine scope, and argument variavbles are added to that.
 * Once the subroutine is called, the input arugments are copied into these predefined locations.
 * 
 * */
std::shared_ptr<int> addSubroutineMapping(std::string name, std::vector<std::string> arguments, int start_line){


    // detect nested subroutines. 
    if(inside_subroutine_flag){
        Logging::logErrorMessage("Nested subroutine detected - Subroutine  " + name + " is declared before the termination of " + current_subroutine_name);
        Logging::logErrorMessage("This is not supported!");
        exit(1);
    }

    // Set temporary line mappings for the start point and end point.
    // the start point is important - this is where we will jump to at the end of the subroutine.
    // The second value of the pair is the return value, this is offset once we've seen the end of the subroutine.
    SUBROUTINE_MAPPING_PAIR.first = LineMapping::addTemporaryLineMapping(start_line);
    SUBROUTINE_MAPPING_PAIR.second = LineMapping::addTemporaryLineMapping(start_line);

    // Add to the subroutine mapping
    SUBROUTINE_MAPPING_ENTRY entry = { SUBROUTINE_MAPPING_PAIR.first, arguments };

    // enter the function scope for the subroutine.
    // This is exited when we see a RETURN statement.
    SymbolTableController::enterFunctionScope(name);

    // For each argument, declare a variable.
    for(int index = 0; index < arguments.size(); index++){
        SymbolTableController::addDeclaredVariable(arguments.at(index), "", ST_ENTRY_TYPE::UNASSIGNED_T);
    }


    // Set the name of the current subroutine
    // and set thee flag indicating that we are currently inside one. 
    current_subroutine_name = name;
    inside_subroutine_flag = true;


    // Finally - add to the mapping and retur the value.
    subroutine_mappings.insert(std::map<std::string, SUBROUTINE_MAPPING_ENTRY>::value_type(name, entry));

    // This mapping will be offset later,
    // the calling class holds a pointer to the value.
    // The calling class maintains this pointer, and once the end of the subroutine ius seen, this value is offset.
    return SUBROUTINE_MAPPING_PAIR.second;
}
/**
 * SUBROUTINE_MAPPING_RETURN getSubroutineMapping(std::string subroutine_name, int return_address, std::vector<std::shared_ptr<ST_ENTRY> > arguments)
 * 
 * This function is the 'calling' method for subroutines. It is responsible for jumping into subroutines, and transferring arguments.
 * Symbol table entries for arugments are passed in. These are then copied (on EDSAC) into the new addresses.
 * 
 * 
 * This copying functionality is what makes subroutines and functions repeatable.
 * 
 **/ 
SUBROUTINE_MAPPING_RETURN getSubroutineMapping(std::string subroutine_name, int return_address, std::vector<std::shared_ptr<ST_ENTRY> > arguments){

    // Find the subroutine entry
    std::map<std::string, SUBROUTINE_MAPPING_ENTRY>::iterator it = subroutine_mappings.begin(); it = subroutine_mappings.find(subroutine_name);
    if( it != subroutine_mappings.end()){

        // This is set for clarity
        SUBROUTINE_MAPPING_ENTRY entry = it->second;

        /**
         * 
         * Generate a warning if too many, or too few, arguments are provided.
         * Exit the subroutine if they are.
         * */
        if(entry.arguments.size() != arguments.size()){
            Logging::logErrorMessage("Warning - Subroutine " + subroutine_name + " takes " + std::to_string(entry.arguments.size())  + ". Found " + std::to_string(arguments.size()));
            return {{}, false};
        } else {

            //Enter the function scope for the subroutinee.
            // Note that we leave the function scope by the end of this mtehod.
            // we need to enter the function scope to access the function arguments, and copy the values of the input arguments into them.
            // Once these arguments have been left, we can exit the function scope. 
            // This is important, as the preceedeing statements after the funcntion call are processed in the normal scope.
            SymbolTableController::enterFunctionScope(subroutine_name);

            // Build a return list. 
            std::vector<std::shared_ptr<ThreeOpCode> > return_toc;

            // Clear the accumulator
            return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("0", THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            

            /*


            For each argument, transfer the argument into a value inside the function scope.
            These values never change, and it is thorugh them that arguments are accessed inside functions.
            **/
            for(int index = 0; index < entry.arguments.size(); index++){
                return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arguments.at(index), THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
                ALL_ST_SEARCH_RESULT arg_var = SymbolTableController::getVariable(entry.arguments.at(index));
                return_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg_var.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            }


            // XSet the mapping of the return address.
            // note that we need to consider the size of the instructions already added.
            std::shared_ptr<int> return_address_mapping = LineMapping::addTemporaryLineMapping(return_address + return_toc.size());


            // Build the return mapping, and exit the function.
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
    if(inside_subroutine_flag){

        current_subroutine_name = "";
        inside_subroutine_flag = false;

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
        exit(1);
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
            SymbolTableController::exitFunctionScope();
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