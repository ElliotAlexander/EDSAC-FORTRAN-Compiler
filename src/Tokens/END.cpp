#include "Tokens/END.h"

bool END::initaliseToken(std::string input){
    // ENDFILE is not implemeented on EDSAC.
    if(input.substr(0,7) == "ENDFILE"){
        Logging::logInfoMessage("Not implemented.");
    } else if(input.substr(0, 3) == "END"){
        // Defensive pro
        if(input.length() == 3){

            // END without a statement - no internal representation is needed. 
            return true;

            // Check fi the syntax matches.
        } else if(input.front() == '(' && input.back() == ')'){

            // Logging - note that this is NOT SUPPORTED.
            Logging::logErrorMessage("END arguments are not supported!");

            /**
             *  This loads a value into an internal repesenttion
             *  END (x,y,z,a,b) is a legacy feature which sets the output switches on the IBM 704 
             *  This is NOT implemented on EDASC.
             * 
             *  Parameterised STOP statements already set the ending vlaue of the accumualtor, so we have no where else to implement this.
             * 
             * We still parse the value though, for clarity
             * 
             * 
             **/ 
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

    // Defensive programming, this should never happen.
    } else {
        Logging::logErrorMessage("Assertation error - Failed to parse END Statement. ");
    }
    return false;
}

std::vector<std::shared_ptr<ThreeOpCode>> END::generatetoc(int starting_address){
    std::vector<std::shared_ptr<ThreeOpCode> > pre_string;
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("", THREE_OP_CODE_OPERATIONS::STOP_PROGRAM, false)));
    return pre_string;
}