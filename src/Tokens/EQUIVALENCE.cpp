#include "Tokens/EQUIVALENCE.h"

bool EQUIVALENCE::initaliseToken(std::string input){
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
                std::cerr << StringConstants::ERROR_TAG << "Failed to load variable list from {" << input << "}" << std::endl;
                std::cerr << StringConstants::ERROR_TAG << "Found nested brackets, but no arguments?" << std::endl;
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
                std::cerr << StringConstants::ERROR_TAG << "Failed to load variable list from {" << input << "}" << std::endl;
                std::cerr << StringConstants::ERROR_TAG << "Found unmatched parenthesis." << std::endl;
                ::printErrorLocation(index-1, input);
                continue;
            }
        } else {
            if(inside_statement_flag){
                argument_list.back().push_back(c);
            } else {
                std::cerr << StringConstants::ERROR_TAG << "Failed to load variable list from {" << input << "}"  << std::endl;
                std::cerr << StringConstants::ERROR_TAG << "Found variables declared outside parenthesis." << std::endl;
                ::printErrorLocation(index-1, input);
                continue;
            }
        }
        index++;
    }


    // Argument list will always exit with a spare, blank variable on the end, unfilled.
    // We need to drop that now.
    argument_list.pop_back();

    //Dump
    for(std::vector<std::string>::iterator it = argument_list.begin(); it != argument_list.end(); ++it) {

        std::map<TOC*, TOC*> argument_mapping;

        // Split on the comma,. A,B -> A and B.
        boost::cmatch loop_matches;
        std::vector<std::string> argument_values;
        boost::split(argument_values, *it, boost::is_any_of(","));

        // Iterate through: x,x,x, and so on.
        if(argument_values.size() == 2){
            TOC* vals[2];
            for (size_t i = 0; i < argument_values.size(); i++) {

                // load control variables into intermediary state.
                vals[i] = ::parseADString(argument_values[i]);

                // Dump raw strings. 
                if(Globals::dump_parsed_values){           
                    std::cout << StringConstants::INFO_TAG << "Loaded Equivalence Argument: [" << vals[i]->toValue() << "]" << std::endl;
                }

            }

            // Build variable mappings.
            argument_mapping.insert(std::pair<TOC*, TOC*>(vals[0], vals[1]));
            equivalence_arguments.push_back(argument_mapping);

        } else {
            std::cerr << StringConstants::ERROR_TAG << "Found too many arguments." << std::endl;
            std::string s;
            s = std::accumulate(std::begin(argument_values), std::end(argument_values), s);
            std::cerr << StringConstants::ERROR_TAG << "Argument {" << s << "} contained " << argument_values.size() << " values. Expected 2" << std::endl;
        }
    }

    return 1;
}

std::vector<TOC*> EQUIVALENCE::generatetoc(std::string input){
    return {};
}