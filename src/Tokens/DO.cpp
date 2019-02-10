#include "Tokens/DO.h"

bool DO::initaliseToken(std::string input){
    if(input.substr(0, 2) == "DO"){

        // Drop the first two chars. 
        input.erase(0,2);
        std::vector<std::string> results;

        // Split by the equals sign. 
        boost::split(results, input, boost::is_any_of("="));
        
        if(Globals::dump_parsed_values){
            std::cout << StringConstants::INFO_TAG << "DO[x]=[y]: x={" << results[0] << "} y={" << results[1] << "}." << std::endl;
        }

        boost::regex control_var_regex("(^([0-9]+))(.*)");
        boost::cmatch char_matches;
        const char *target_leftofequals = results.at(0).c_str();

        // Parse control variables to the left of the equals sign.
        if (boost::regex_match(target_leftofequals, char_matches, control_var_regex))
        {
            if(char_matches.length() < 3){
                std::cerr << StringConstants::ERROR_TAG << "Syntax Error - failed to parse control variables for line {" << input << "}" << std::endl;
                return false;
            }

            // Load Control Variables to the left of the equals sign.
            int control_loop = boost::lexical_cast<int>(char_matches[1]);
            std::string main_loop = char_matches[3];

            if(Globals::dump_parsed_values){
                std::cout << StringConstants::INFO_TAG << "Control Loop Variable: " << control_loop << std::endl;
                std::cout << StringConstants::INFO_TAG << "Main Loop Variable: " <<  main_loop << std::endl;
            }
        } else {
            std::cerr << StringConstants::ERROR_TAG <<  "Syntax Error - failed to parse control variables from line {" << input << "}" << std::endl;
            std::cerr << StringConstants::ERROR_TAG << "Control Variable failed to load from pattern: " << control_var_regex << std::endl;
        }

        boost::cmatch loop_matches;
        std::vector<std::string> control_vars_right;
        const char* target = results.at(1).c_str();
        boost::split(control_vars_right, target, boost::is_any_of(","));
        if(control_vars_right.size() > 0){
            if(Globals::dump_parsed_values){           
                for (size_t i = 0; i < control_vars_right.size(); i++) {
                    TOC* x = ::parseADString(control_vars_right[i]);
                    std::cout << StringConstants::INFO_TAG << "Control Variable [" << i << "]{" << control_vars_right[i] << "}." << std::endl;
                }
            }
        } else {
            std::cout << StringConstants::ERROR_TAG << "Syntax Error - Failed to load control variables. {" << target << "}." << std::endl;
            return false;
        }

        // TODO - arithmetic / variable parsing of control vars. 


        return true;
    } else {
        std::cout << "Syntax error!" << std::endl;
        return false;
    }
}

std::vector<TOC*> DO::generatetoc(std::string input){
    return {};
}