#include "Tokens/READ.h"

bool READ::initaliseToken(std::string input){
    if(input.substr(0,4) == "READ"){
        READ::variable_name = input.erase(0,4);
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded read statement for variable : " + READ::variable_name);
        return true;
    } else {
        Logging::logErrorMessage("Error - failed to load READ statement.");
    }
    return true;
}

std::vector<std::shared_ptr<ThreeOpCode>> READ::generatetoc(int starting_address){
    std::vector<std::shared_ptr<ThreeOpCode> > pre_string;
    ALL_ST_SEARCH_RESULT entry = SymbolTableController::getVariable(READ::variable_name);
    Logging::logConditionalErrorMessage(!entry.found, "Error - failed to find variable " + READ::variable_name + ".");
    std::shared_ptr<ST_ENTRY> use_entry;
    if(!entry.found){
        use_entry = SymbolTableController::addDeclaredVariable(READ::variable_name, "", ST_ENTRY_TYPE::UNASSIGNED_T);
        Logging::logInfoMessage("Adding new variable " + READ::variable_name);
    } else {
        use_entry = entry.result;
    }

    Libs::enableRoutine("M20");
    std::string m20_text = Libs::getLibraryContent("M20");


    ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
    Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");
	pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("0", THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, std::string("F" + m20_text))));
	pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("45", THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
	pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("16", THREE_OP_CODE_OPERATIONS::SHIFT_ACCUMULATOR_RIGHT, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(use_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));

    return pre_string;
}