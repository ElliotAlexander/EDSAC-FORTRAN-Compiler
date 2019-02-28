#include "Tokens/END.h"

bool END::initaliseToken(std::string input){
    if(input.substr(0,7) == "ENDFILE"){
        // TODO - Not imiplemented
    } else if(input.substr(0, 3) == "END"){
        if(input.length() == 3){
            return true;
        } else if(input.front() == '(' && input.back() == ')'){
            argument_list_set = true;
            input.erase(0,1);
            input.pop_back();
            std::vector<std::string> end_argument_list;
            boost::split(end_argument_list, input, boost::is_any_of(","));

            int index = 0;
            for(std::vector<std::string>::iterator it = end_argument_list.begin(); it != end_argument_list.end(); ++it){
                argument_list.push_back(::parseADString(*it));
                if(Globals::dump_parsed_values){
                    std::cout << StringConstants::INFO_TAG << "Loaded end argument [" << std::to_string(index) << "]: " << argument_list.back()->toValue() << std::endl;;
                }
                index++;
            }
            return true;
        } else { 
            std::cerr << StringConstants::ERROR_TAG << "Failed to parse END Statement." << std::endl;
        }
    } else {
        // TODO - tidy all these messages up
        std::cerr << StringConstants::ERROR_TAG << "Failed to parse END Statement." << std::endl;
    }
    return false;
}

std::vector<RDParseTreeNode*> END::generatetoc(std::string input){
    return {};
}