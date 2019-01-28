#include "Tokens/DO.h"

bool DO::tokenize(std::string input){
    std::string first_two = input.substr(0, 2);
    if(first_two == "DO"){
        input.erase(0,2);

        std::vector<std::string> results;
        boost::split(results, input, [](char c){return c == '=';});
        std::cout << results[0] << std::endl;

        boost::regex date_regex("(^([0-9]+))(.*)");
        boost::cmatch char_matches;
        const char *input_cstr = "12031230HELLO12WQEWQ";
        const char *target = results.at(0).c_str();
        if (boost::regex_match(target, char_matches, date_regex))
        {
            int control_loop = boost::lexical_cast<int>(char_matches[1]);
            std::cout << "Control Loop Variable: " << control_loop << std::endl;
            std::cout << "Main Loop Variable: " <<  char_matches[2] << std::endl;
        } else {
            std::cout << "No match" << std::endl;
        }
        return true;
    } else {
        std::cout << "Syntax error!" << std::endl;
    }

    return false;
}

