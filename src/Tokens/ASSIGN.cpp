#include "Tokens/ASSIGN.h"

bool ASSIGN::initaliseToken(std::string input){
    if(input.substr(0, 6) == "ASSIGN"){
        std::string input_backup = input;
        input.erase(0,6);


        // We need ot handle this a bit differently
        // For silly reasons, ASSIGN doesn't use an equalls operator,
        // Case: what if a variable name is TOTO
        // ASSIGNTOTOTO5 would be valid.

        std::size_t found = input.find_last_of("TO");

        std::string variable_name_temp = input.substr(0, found-1);
        if(variable_name_temp.length() < 1){
            std::cerr << StringConstants::ERROR_TAG << "Failed to parse variable name." << std::endl;
            ::printErrorLocation(found-1, input);
        }

        std::string assignment_string_temp = input.substr(found+1, input.length() );
        if(assignment_string_temp.length() < 1){
            std::cerr << StringConstants::ERROR_TAG << "Failed to parse assignment value." << std::endl;
            ::printErrorLocation(found+1, input);
        }


        ASSIGN::variable_name = variable_name_temp;
        ASSIGN::assignment_value_string = assignment_string_temp;

        if(Globals::dump_parsed_values){
            std::cout << StringConstants::INFO_TAG << "Loaded variable name : " << variable_name_temp << std::endl;
            std::cout << StringConstants::INFO_TAG << "Loaded variable assignment : " << assignment_string_temp << std::endl;
        }

        return true;
    } else {
        std::cerr << StringConstants::ERROR_TAG << "Failed to load ASSIGN token - couldn't parse ASSIGN keyword." << std::endl;
        printErrorLocation(0, input);
        return false;
    }
}

std::vector<TOC*> ASSIGN::generatetoc(std::string input){
    return {};
}