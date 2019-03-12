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
        DO::control_loop_var_toc = ::parseADString(char_matches[1]); 
        DO::main_loop_var_toc = ::parseADString(char_matches[3]);
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
        for(int i = 0; i < control_vars_right.size(); i++){
            DO::control_vars_right_toc.push_back(::parseADString(control_vars_right.at(i)));
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values,"Loaded instruction value { " + control_vars_right.at(i) + " }");
        }
        return true;
    } else {
        Logging::logErrorMessage("Syntax Error - Failed to load control variables. {" + rhs_input_string + "}");
        return false;
    }
}

std::vector<std::shared_ptr<ThreeOpCode>> DO::generatetoc(){
    return {};
}