#include "Tokens/IF.h"
// TODO save the full string to a class member, improve output.
bool IF::initaliseToken(std::string input){
    std::string input_noIF = stripIFTag(input);
    StringOperationContainer checkedFixedArguments = parseFixedConditionalString(input_noIF);
    if(!checkedFixedArguments.result){
        StringOperationContainer parsedArithmeticArgument = parseConditionalArgument(checkedFixedArguments.input_string);
        parseRightHandSideArguments(parsedArithmeticArgument.input_string);
    } else {
        parseRightHandSideArguments(checkedFixedArguments.input_string);
    }
    return true;
}

std::string IF::stripIFTag(std::string input){
    if(!(input.substr(0,2) == "IF")){
        Logging::logErrorMessage("Syntax Error - Failed to parse IF Statement. ");
        Logging::logErrorMessage("Full statement: { " + input + "}. ");
    } else {
        input.erase(input.find("IF"), 2);
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded IF String: " + input);
    }
    return input;
}

StringOperationContainer IF::parseFixedConditionalString(std::string conditional_string){
    if(conditional_string.at(0) == '('){
        std::string output_string;
        if(conditional_string.substr(1,11) == "SENSESWITCH" || conditional_string.substr(1,10) == "SENSELIGHT"){
            std::string statement_type_string;
            if(conditional_string.substr(1,11) == "SENSESWITCH"){
                conditional_string.erase(1,11);
                statement_type = IF_STATEMENT_TYPE::SENSESWITCH;
                output_string = "SENSE SWITCH";
            } else if(conditional_string.substr(1,10) == "SENSELIGHT"){
                conditional_string.erase(1,10);
                statement_type = IF_STATEMENT_TYPE::SENSELIGHT;
                output_string = "SENSE LIGHT";
            } else {
                Logging::logErrorMessage("An unknown error occured loading conditional string: " + conditional_string);
                ::printErrorLocation(1, conditional_string);
            }

            std::string integer_string;
            int index = 0;


            // Strip the initial (
            conditional_string.erase(0,1);


            // TODO - Could support nested parenthesis in the integer string? Not 100% sure on the effect of this however. 
            for(char&c : conditional_string){
                if(c == ')'){
                    index++;
                    break;
                } else {
                    index++;
                    integer_string.push_back(c);
                }
            }


            conditional_variable = ::parseADString(integer_string);
            conditional_string.erase(0, index);
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values,  "Loaded fixed value: " + output_string);
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values,  "Loaded conditional value: " + conditional_variable->toValue());
            return StringOperationContainer{conditional_string, true};
        } else {
            return StringOperationContainer{conditional_string, false};
        }
    } else {
        std::string output_string;
        if(conditional_string.substr(0,19) == "ACCUMULATOROVERFLOW" || conditional_string.substr(0,16) == "QUOTIENTOVERFLOW" || conditional_string.substr(0,11) == "DIVIDECHECK"){
            if(conditional_string.substr(0,19) == "ACCUMULATOROVERFLOW"){
                statement_type = IF_STATEMENT_TYPE::ACCUMULATOROVERFLOW;
                conditional_string.erase(0,20);
                output_string = "ACCUMULATOR OVERFLOW";
            } else if(conditional_string.substr(0,16) == "QUOTIENTOVERFLOW") {
                statement_type = IF_STATEMENT_TYPE::QUOTIENTOVERFLOW;
                conditional_string.erase(0,16);
                output_string = "QUOTIENTOVERFLOW";
            } else if(conditional_string.substr(0,11) == "DIVIDECHECK") {
                statement_type = IF_STATEMENT_TYPE::DIVIDECHECK;
                conditional_string.erase(0,11);
                output_string = "DIVIDECHECK";
            } else {
                Logging::logErrorMessage("An unknown error occured loading conditional string. Full Statement { " + conditional_string + " }.");
                ::printErrorLocation(1, conditional_string);
            }
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded fixed conditional value: " + output_string);
        } else {
            return StringOperationContainer{conditional_string, false};
        }
    }
    return StringOperationContainer{conditional_string, true};
}


StringOperationContainer IF::parseConditionalArgument(std::string conditional_string_input){
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
    for(char&c : conditional_string_input){
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
                Logging::logWarnMessage(" Warning - Possible syntax error. Was expecting '(', found '" + std::to_string(c) + "'.");
                ::printErrorLocation(index + 2, conditional_string_input);
            }
        }
        index++;
    }
    conditional_string_input.erase(0,index);
    conditional_variable = ::parseADString(conditional_variable_string);
    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Parsed conditional value succcessfully: " + conditional_variable_string);
    return StringOperationContainer{conditional_string_input, true};
}

bool IF::parseRightHandSideArguments(std::string rhs_input_string){

    // Breakup string by commas. 
    std::vector<std::string> instruction_values_arr;
    boost::split(instruction_values_arr, rhs_input_string, boost::is_any_of(","));
    // Iterate through: x,x,x, and so on.
    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded right hand side string " + rhs_input_string);
    if(instruction_values_arr.size() > 0){
        if(instruction_values_arr.size() > 3){
            Logging::logErrorMessage( "Found too many instructions in IF statement. Expected 2|3, found " + std::to_string(instruction_values_arr.size()));
            Logging::logErrorMessage("Full statement: { " + rhs_input_string + " }.");    
        } else if(instruction_values_arr.size() == 1){
            Logging::logErrorMessage("Found too few instructions in IF statement. Expected 2|3, found " + std::to_string(instruction_values_arr.size()));
            Logging::logErrorMessage("Full statement: { " + rhs_input_string + " }.");
        } else {
            int index = instruction_values_arr.size();
            for(int i = 0; i < index; i++){
                instruction_values.push_back(::parseADString(instruction_values_arr.at(i)));
                Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded instruction [" + std::to_string(i) + "]:" + instruction_values_arr.at(i));
            }
            return true;
        }
        return false;
    } else {
        Logging::logErrorMessage("Syntax Error - IF Statement instruction values are improperly formatted.");
        Logging::logErrorMessage("Expected format is: \nIF (<Conditional>) <Line label>, <Line label> [,<Line label>]");
        return false;
    }
}

std::vector<TOC*> IF::generatetoc(std::string input){
    return {};
}