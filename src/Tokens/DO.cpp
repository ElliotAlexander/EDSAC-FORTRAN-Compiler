#include "Tokens/DO.h"

bool DO::initaliseToken(std::string input){
    if(input.substr(0, 2) == "DO"){

        input.erase(0,2);
        std::vector<std::string> results;

        // Split by the equals sign. 
        boost::split(results, input, boost::is_any_of("="));
        std::string target_leftofequals = results[0];
        std::string target_rightofequals = results[1];

        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "DO[x]=[y]: x={" + results[0] +  "} y={" + results[1] + "}.");
        return parseLeftHandSide(target_leftofequals) && parseRightHandSide(target_rightofequals) ? true : false;
    } else {
        Logging::logErrorMessage("Syntax Error - Failed to parse DO Statement. ");
        Logging::logErrorMessage( "Full statement: { " + input + "}. ");
        return false;  
    }
}


bool DO::parseLeftHandSide(std::string lhs_input_string){

    // Pull first control variable out of string 
    // Note that this must be a number
    // DO <Number><Variable> = <Arith>,<Arith>(optional->),<Arith>
    boost::regex control_var_regex("(^([0-9]+))(.*)");
    boost::cmatch char_matches;
    // Parse control variables to the left of the equals sign.

    if (boost::regex_match(lhs_input_string.c_str(), char_matches, control_var_regex))
    {
        if(char_matches.length() < 3){
            Logging::logErrorMessage( "Syntax Error - failed to parse control variables for line {" + lhs_input_string + "}");
            return false;
        }

        // Load Control Variables to the left of the equals sign.
        DO::line_label_loop_end = char_matches[1]; 
        DO::main_loop_var_toc = char_matches[3];

        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Control Loop Variable: " + char_matches[1]);
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Main Loop Variable: " +  char_matches[3]);
        return true;
    } else {
        Logging::logErrorMessage("Syntax Error - failed to parse control variables from line {" + lhs_input_string + "}");
        return false;
    }
}


bool DO::parseRightHandSide(std::string rhs_input_string){
    // Breakup string by commas. 
    boost::cmatch loop_matches;
    std::vector<std::string> control_vars_right;
    boost::split(control_vars_right, rhs_input_string, boost::is_any_of(","));
    // Iterate through: x,x,x, and so on.
    if(control_vars_right.size() > 0){
        if(control_vars_right.size() < 2 || control_vars_right.size() > 3){
            Logging::logErrorMessage("Failed to load control vars. ");
            // TODO
            return false;
        } else {
            DO::loop_start_value = std::stoi(control_vars_right[0]);
            DO::loop_end_value = std::stoi(control_vars_right[1]);
            DO::loop_iteration_amount = (control_vars_right.size() > 2) ? std::stoi(control_vars_right[2]) : 1;
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded control loop variables:");
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "DO Loop start: " + std::to_string(DO::loop_start_value));
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "DO Loop end: " + std::to_string(DO::loop_end_value));
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "DO Loop iteration amount: " + std::to_string(DO::loop_iteration_amount));
            return true;
        }
    } else {
        Logging::logErrorMessage("Syntax Error - Failed to load control variables. {" + rhs_input_string + "}");
        return false;
    }
    return false;
}

std::vector<std::shared_ptr<ThreeOpCode>> DO::generatetoc(int starting_address){
    std::vector<std::shared_ptr<ThreeOpCode> > pre_string;

    ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
	Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");

    std::shared_ptr<int> loop_top_mapping = LineMapping::addTemporaryLineMapping(starting_address + 5);

    std::shared_ptr<ST_ENTRY> loop_counter_end_check = SymbolTableController::addTemp(std::to_string(DO::loop_end_value - DO::loop_start_value + 2), ST_ENTRY_TYPE::UNASSIGNED_T);
    std::shared_ptr<ST_ENTRY> loop_iteration_variable = SymbolTableController::addTemp(std::to_string(loop_iteration_amount), ST_ENTRY_TYPE::UNASSIGNED_T);
    std::shared_ptr<ST_ENTRY> user_visible_loop_counter = SymbolTableController::addDeclaredVariable(DO::main_loop_var_toc , std::to_string(loop_start_value - 1), ST_ENTRY_TYPE::UNASSIGNED_T);
    
    std::shared_ptr<ST_ENTRY> loop_counter_backup = SymbolTableController::addTemp(std::to_string(loop_start_value - 1), ST_ENTRY_TYPE::UNASSIGNED_T);
    std::shared_ptr<ST_ENTRY> loop_counter_end_check_backup = SymbolTableController::addTemp(std::to_string(DO::loop_end_value + 1), ST_ENTRY_TYPE::UNASSIGNED_T);


    std::shared_ptr<int> loop_end_address = DoLoopMapping::addDoLoopMapping(std::stoi(DO::line_label_loop_end), loop_top_mapping);

    // Pre Loop
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_counter_backup, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(user_visible_loop_counter, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_counter_end_check_backup, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_counter_end_check, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));

    // Enter Loop
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(user_visible_loop_counter, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_iteration_variable, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(user_visible_loop_counter, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACCUMULATOR_NO_CLEAR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_counter_end_check, THREE_OP_CODE_OPERATIONS::SUBTRACT_TO_ACCUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_end_address, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_POSTITIVE, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));

    return pre_string;

}