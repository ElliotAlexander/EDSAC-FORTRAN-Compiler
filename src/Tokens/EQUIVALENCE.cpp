#include "Tokens/EQUIVALENCE.h"

bool EQUIVALENCE::initaliseToken(std::string input){
    if(input.substr(0, 11) == "EQUIVALENCE") {
        input.erase(input.find("EQUIVALENCE"), 11);

        // Break the arguments up by their bracketting. 
        // Store this in a vector, i.e. (A,B) (D,E) becomes A,B and D,E within argument_list.
        std::vector<std::string> argument_list;
        argument_list.push_back(std::string(""));
        int inside_statement_flag = 0;
        int index = 1;
        for(char& c : input) {
            if(c == '('){
                if(inside_statement_flag){
                    Logging::logErrorMessage("Failed to load variable list from {" + input + "}");
                    Logging::logErrorMessage("Found nested brackets, but no arguments?");
                    ::printErrorLocation(index-1, input);
                    continue;
                } else {
                    inside_statement_flag = 1;
                }
            } else if (c == ')'){
                if(inside_statement_flag){
                    inside_statement_flag = 0;
                    argument_list.push_back(std::string(""));
                } else {
                    Logging::logErrorMessage("Failed to load variable list from {" + input + "}");
                    Logging::logErrorMessage("Found unmatched parenthesis.");
                    ::printErrorLocation(index-1, input);
                    continue;
                }
            } else {
                if(inside_statement_flag){
                    argument_list.back().push_back(c);
                } else {
                    Logging::logErrorMessage("Failed to load variable list from {" + input + "}");
                    Logging::logErrorMessage("Found variables declared outside parenthesis.");
                    ::printErrorLocation(index-1, input);
                    continue;
                }
            }
            index++;
        }

        // Argument list will always exit with a spare, blank variable on the end, unfilled.
        // We need to drop that now.
        argument_list.pop_back();



        int argument_index = 0;
        //Dump
        for(std::vector<std::string>::iterator it = argument_list.begin(); it != argument_list.end(); ++it) {

            // Split on the comma,. A,B -> A and B.
            boost::cmatch loop_matches;
            std::vector<std::string> argument_values;
            boost::split(argument_values, *it, boost::is_any_of(","));

            // Iterate through: x,x,x, and so on.
            if(argument_values.size() == 2){
                for (size_t i = 0; i < argument_values.size(); i++) {
                    equivalence_arguments.at(argument_index).push_back(::parseADString(argument_values[i]));
                    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded Equivalence Argument: [" + argument_values[i] +"]");
                }
            } else {
                std::string s;
                std::accumulate(std::begin(argument_values), std::end(argument_values), s);
                Logging::logErrorMessage( "Found too many arguments.");
                Logging::logErrorMessage("Argument {" + s + "} contained " + std::to_string(argument_values.size()) + " values. Expected 2");
            }
            argument_index++;
        }
        return true;
    } else {
        Logging::logErrorMessage( "Syntax Error - Failed to parse EQUIVALENCE Statement. ");
        Logging::logErrorMessage("Full statement: { " + input + "}. ");
        return false;  
    }

}

std::vector<std::shared_ptr<ThreeOpCode>> EQUIVALENCE::generatetoc(){
    return {};
}