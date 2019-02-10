#include "Tokens/DO.h"

bool DO::initaliseToken(std::string input){
    if(input.substr(0, 2) == "DO"){

        // Drop the first two chars. 
        input.erase(0,2);
        std::vector<std::string> results;

        // Split by the equals sign. 
        boost::split(results, input, boost::is_any_of("="));
        
        // If enable - dump parsed values.
        if(Globals::dump_parsed_values){
            std::cout << StringConstants::INFO_TAG << "DO[x]=[y]: x={" << results[0] << "} y={" << results[1] << "}." << std::endl;
        }

        const char *target_leftofequals = results.at(0).c_str();

        // Pull first control variable out of string 
        // Note that this must be a number
        // DO <Number><Variable> = <Arith>,<Arith>(optional->),<Arith>
        boost::regex control_var_regex("(^([0-9]+))(.*)");
        boost::cmatch char_matches;

        // Parse control variables to the left of the equals sign.
        if (boost::regex_match(target_leftofequals, char_matches, control_var_regex))
        {
            if(char_matches.length() < 3){
                std::cerr << StringConstants::ERROR_TAG << "Syntax Error - failed to parse control variables for line {" << input << "}" << std::endl;
                return false;
            }

            // Load Control Variables to the left of the equals sign.
            control_loop_var_toc = ::parseADString(char_matches[1]); 
            main_loop_var_toc = ::parseADString(char_matches[3]);


            // If enabled - dump output.
            if(Globals::dump_parsed_values){
                std::cout << StringConstants::INFO_TAG << "Control Loop Variable: " << control_loop_var_toc->toValue() << std::endl;
                std::cout << StringConstants::INFO_TAG << "Main Loop Variable: " <<  main_loop_var_toc->toValue() << std::endl;
            }
        } else {
            std::cerr << StringConstants::ERROR_TAG <<  "Syntax Error - failed to parse control variables from line {" << input << "}" << std::endl;
            std::cerr << StringConstants::ERROR_TAG << "Control Variable failed to load from pattern: " << control_var_regex << std::endl;
        }

        
        
        const char* target_rightofequals = results.at(1).c_str();


        // Breakup string by commas. 
        boost::cmatch loop_matches;
        std::vector<std::string> control_vars_right;
        boost::split(control_vars_right, target_rightofequals, boost::is_any_of(","));


        // Iterate through: x,x,x, and so on.
        if(control_vars_right.size() > 0){
            for (size_t i = 0; i < control_vars_right.size(); i++) {

                // load control variables into intermediary state.
                control_vars_right_toc[i] = ::parseADString(control_vars_right[i]);

                // Dump raw strings. 
                if(Globals::dump_parsed_values){           
                    std::cout << StringConstants::INFO_TAG << "Control Variable [" << control_vars_right_toc[i]->toValue() << "]{" << control_vars_right[i] << "}." << std::endl;
                }
            }
        } else {
            std::cout << StringConstants::ERROR_TAG << "Syntax Error - Failed to load control variables. {" << target_rightofequals << "}." << std::endl;
            return false;
        }

        return true;
    } else {
        std::cout << "Syntax error!" << std::endl;
        return false;
    }
}

std::vector<TOC*> DO::generatetoc(std::string input){
    return {};
}