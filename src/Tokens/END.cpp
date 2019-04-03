#include "Tokens/END.h"

bool END::initaliseToken(std::string input){
    if(input.substr(0,7) == "ENDFILE"){
        // TODO - Not imiplemented
        Logging::logInfoMessage("Not implemented.");
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
                Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded end argument [ " + std::to_string(index) + "]: " + (*it));
                index++;
            }
            return true;
        } else { 
            Logging::logErrorMessage("Failed to parse END Statement.");
        }
    } else {
        // TODO - tidy all these messages up
        Logging::logErrorMessage("Failed to parse END Statement. ");
    }
    return false;
}

std::vector<std::shared_ptr<ThreeOpCode>> END::generatetoc(int starting_address){
    //std::vector<std::shared_ptr<ThreeOpCode> > pre_string;
    //pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("", THREE_OP_CODE_OPERATIONS::STOP_PROGRAM, false)));
    //return pre_string;
    return {};
}