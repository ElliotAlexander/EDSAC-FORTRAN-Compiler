#include "Tokens/IF.h"

bool IF::initaliseToken(std::string input){


    // backup input so we can print it in errors.
    std::string input_original = input;


    // Strip the IF
    input.erase(input.find("IF"), 2);
    if(Globals::dump_parsed_values){
        std::cout << StringConstants::INFO_TAG << "Loaded IF String: " << input << std::endl;
    }


    // We're now expecting a string in the format:
    // (xxx) a,b,c
    // We need to pull out the value between the parenthesis, while allowing nested parenthesis.
    // This could be done with regex, but doing it by hand seems faster, with more scope for informative errors.
    int nested_parens = 0;
    bool inside_parens = false;
    // Index needs to start at 3, because we'll be printing the whole stirng.
    // i.e. minus the IF. 
    int index = 0;

    // We'll build the string in this variable.
    std::string conditional_variable_string;
    for(char&c : input){
        if(inside_parens){
            if(c == ')'){
                if(nested_parens == 0){
                    inside_parens = false;
                    // When we break, the final index won't be called.
                    // Hence, add it here to avoid skipping the final character.
                    index++;
                    break;
                } else {
                    nested_parens--;
                }
            } else if (c == '('){
                nested_parens++;
            }
            conditional_variable_string.push_back(c);
        } else {
            if(c == '('){
                inside_parens = 1;
            } else {
                std::cerr << StringConstants::WARN_TAG << " Warning - Possible syntax error. Was expecting '(', found '" << c << "'." << std::endl;
                ::printErrorLocation(index + 2, input_original);
            }
        }
        index++;
    }


    conditional_variable = ::parseADString(conditional_variable_string);

    if(Globals::dump_parsed_values){
        std::cout << StringConstants::INFO_TAG << "Loaded conditional string successfully: " << conditional_variable_string << std::endl;
        std::cout << StringConstants::INFO_TAG << "Parsed conditional value succcessfully: " << conditional_variable->toValue() << std::endl;
    }

    // End conditional values

    std::string instruction_values_string = input.substr(index, input.length()-1);

    // TODO - The token identification / regex doesn't account for missing tokens.
    // We can fix this programatically, but should probably also update the regex.
    // Hence TODO!
    if(instruction_values_string.length() < 1){
        std::cerr << StringConstants::ERROR_TAG << "Failed to load instruction values - no string found." << std::endl 
            << StringConstants::ERROR_TAG << "String following conditional value was blank." << std::endl
            << StringConstants::ERROR_TAG << "Full statement: { " << input_original << " }." << std::endl;
        // Note that we need + 1 in index for the first charcter after the conditional, and +2 for the IF we removed at the beginning.
        ::printErrorLocation(index + 3, input_original);
        return 0;
    }

    // Breakup string by commas. 
    std::vector<std::string> instruction_values_arr;
    boost::split(instruction_values_arr, instruction_values_string, boost::is_any_of(","));

    // Iterate through: x,x,x, and so on.
    if(instruction_values_arr.size() > 0){
        if(instruction_values_arr.size() > 3){
            std::cerr << StringConstants::ERROR_TAG << "Found too many instructions in IF statement. Expected 2|3, found " << instruction_values_arr.size() << std::endl
            << StringConstants::ERROR_TAG << "Full statement: { " << input_original << " }." << std::endl;
            return 0;
        } else if(instruction_values_arr.size() == 1){
            std::cerr << StringConstants::ERROR_TAG << "Found too few instructions in IF statement. Expected 2|3, found " << instruction_values_arr.size() << std::endl
            << StringConstants::ERROR_TAG << "Full statement: { " << input_original << " }." << std::endl;
            return 0;
        } else {
            int index = instruction_values_arr.size();
            for(int i = 0; i < index; i++){
                TOC* y = ::parseADString(instruction_values_arr.at(i));
                instruction_values.push_back(y);
                if(Globals::dump_parsed_values){
                    std::cout << StringConstants::INFO_TAG << "Loaded instruction variable: " << y->toValue() << "." << std::endl;
                }
            }
            return 1;
        }
    } else {
        std::cerr << StringConstants::ERROR_TAG << "Syntax Error - IF Statement instruction values are improperly formatted. " << std::endl
        << StringConstants::ERROR_TAG << "Expected format is: \nIF (<Conditional>) <Line label>, <Line label> [,<Line label>]" << std::endl;
        return 0;
    }
} 

std::vector<TOC*> IF::generatetoc(std::string input){
    return {};
}