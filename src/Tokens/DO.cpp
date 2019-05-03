#include "Tokens/DO.h"

bool DO::initaliseToken(std::string input){
    if(input.substr(0, 2) == "DO"){

        // erase the keyword string.
        input.erase(0,2);

        // setup a variable to dump values into.
        std::vector<std::string> results;

        // Split by the equals sign. 
        boost::split(results, input, boost::is_any_of("="));

        /**
         * 
         * Split the string left and right of the equals sign. Load each string into it's own value.
         * 
         **/ 
        std::string target_leftofequals = results[0];
        std::string target_rightofequals = results[1];


        // Output an information message ot the user.
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "DO[x]=[y]: x={" + results[0] +  "} y={" + results[1] + "}.");

        /**
         * 
         * These two functions take the left and right hand side, and are responsible for loading each into member variables. If either of them fails, the class as a whole fails.
         * */
        return parseLeftHandSide(target_leftofequals) && parseRightHandSide(target_rightofequals) ? true : false;
    } else {

        // Defensive programming - this shouldn't happen.
        // Regex should match this. 
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


    /**
     * Match the above string, This method  takes multiple regex strings, and breaks down a larger string into them
     * This fucntion pulls out the integer at the start of the statement, leaving the rest of the string in a second token.
     * Reading the docs on this fucntion is probably advisable before attempting to change it.
     * 
     **/ 
    if (boost::regex_match(lhs_input_string.c_str(), char_matches, control_var_regex))
    {

        // This is an indicator that the regex has failed.
        if(char_matches.length() < 3){
            // Erorr - return false, fail back upto the statement level.
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

        // if the regex fails - we probably have some invalid syntax.
        // Regex should catch this, so this is a defensive check.
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
        // we need either 2 or 3 control vars.
        // Nothing else is acceptable
        if(control_vars_right.size() < DO_LOOP_MINIMUM_SIZE || control_vars_right.size() > DO_LOOP_MAXIMUM_SIZE){
            Logging::logErrorMessage("Failed to load control vars. ");
            return false;
        } else {

            // Load each control var into a member variable.
            // The first two are interpreted as ints. These should always be integers(Regex is covering this).
            DO::loop_start_value = std::stoi(control_vars_right[0]);
            DO::loop_end_value = std::stoi(control_vars_right[1]);

            // The third variable is optional.
            // If it's set - use it. Else use a constant default (1).
            // This represents the iteration amount fo a do loop, i.e. how much we add to the control variable each loop.
            DO::loop_iteration_amount = (control_vars_right.size() > 2) ? std::stoi(control_vars_right[2]) : DO_LOOP_DEFAULT_ITERATION_AMOUNT;
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


    // This is our waste - all unused accumulator values are cleared into this.
    ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
	Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");


    // This it the mapping for the top of the DO loop
    std::shared_ptr<int> loop_top_mapping = LineMapping::addTemporaryLineMapping(starting_address + 5);


    /**
     * 
     *  This block of instructions restores the values of the DO loop variables from backups.
     *  The backups are important for allowing the loop to run more than once.
     *  Without backups, the code could only be run once, the variables would be modified, andthen it would break the second time round
     *  
     **/ 
    std::shared_ptr<ST_ENTRY> loop_counter_end_check = SymbolTableController::addTemp(std::to_string(DO::loop_end_value - DO::loop_start_value + 2), ST_ENTRY_TYPE::UNASSIGNED_T);
    std::shared_ptr<ST_ENTRY> loop_iteration_variable = SymbolTableController::addTemp(std::to_string(loop_iteration_amount), ST_ENTRY_TYPE::UNASSIGNED_T);
    std::shared_ptr<ST_ENTRY> user_visible_loop_counter = SymbolTableController::addDeclaredVariable(DO::main_loop_var_toc , std::to_string(loop_start_value - 1), ST_ENTRY_TYPE::UNASSIGNED_T);
    
    std::shared_ptr<ST_ENTRY> loop_counter_backup = SymbolTableController::addTemp(std::to_string(loop_start_value - 1), ST_ENTRY_TYPE::UNASSIGNED_T);
    std::shared_ptr<ST_ENTRY> loop_counter_end_check_backup = SymbolTableController::addTemp(std::to_string(DO::loop_end_value + 1), ST_ENTRY_TYPE::UNASSIGNED_T);

    // Add a mapping for the end of the loop - this is where we jump to when the loop is over.
    std::shared_ptr<int> loop_end_address = DoLoopMapping::addDoLoopMapping(std::stoi(DO::line_label_loop_end), loop_top_mapping);

    // Pre Loop
    // See above about backups
    // This is NOT a part of the loop, and is where the backups are regenerated.
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_counter_backup, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(user_visible_loop_counter, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_counter_end_check_backup, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_counter_end_check, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));

    // Enter Loop
    // This is the start of the loop
    // Code injected at the bottom ot he do loop jumps us back here.
    // This set of instructions iterates a variable, checks it against the final var, and jumps to the end of the loop if they're equal.
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(user_visible_loop_counter, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_iteration_variable, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(user_visible_loop_counter, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACCUMULATOR_NO_CLEAR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_counter_end_check, THREE_OP_CODE_OPERATIONS::SUBTRACT_TO_ACCUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_end_address, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_POSTITIVE, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));

    return pre_string;

}