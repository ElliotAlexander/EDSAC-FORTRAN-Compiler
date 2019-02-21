#include "Tokens/GOTO.h"

bool GOTO::initaliseToken(std::string input){
    if(input.substr(0,4) == "GOTO"){

        input.erase(input.find("GOTO"), 4);

        if(Globals::dump_parsed_values){
            std::cout << StringConstants::INFO_TAG << "Loaded GOTO String: " << input << std::endl;
        }   


        // There are several options for how the arguments for a GOTO statement can be formatted.
        // Pick them apart in this function, and return them in a data structure.
        ARG_LIST_WRAPPER wrapper = GOTO::loadArgumentString(input);

        // We always have a single arg
        GOTO::loadSingleArgumentValue(wrapper.single_arg);

        // We optionally have a list of other arguments. 
        if(wrapper.arg_list_set){
            GOTO::loadArgumentListValue(wrapper.arg_list);
        }
        
        return 1;
    } else {
        std::cerr << StringConstants::ERROR_TAG << "Syntax Error - Failed to parse GOTO Statement. " << std::endl 
        << StringConstants::ERROR_TAG << "Full statement: { " << input << "}. " << std::endl;
        return 0;  
    }
}


void GOTO::loadSingleArgumentValue(std::string argument_string){
    goto_single_arg = ::parseADString(argument_string);
}

void GOTO::loadArgumentListValue(std::string argument_list_string){

    if(argument_list_string.front() == '('){
        argument_list_string.erase(0,1);
    }

    if(argument_list_string.back() == ')'){
        argument_list_string.pop_back();
    }

    std::vector<std::string> argument_split;
    boost::split(argument_split, argument_list_string, boost::is_any_of(","));
    for(std::vector<std::string>::iterator it = argument_split.begin(); it != argument_split.end(); ++it){
        if(Globals::dump_parsed_values){
            std::cout << StringConstants::INFO_TAG << "Loaded Argument List value: " << *it << std::endl;
        }
        goto_arg_list.push_back(::parseADString(*it));
        std::cout << StringConstants::INFO_TAG << "Parsed value: " << goto_arg_list.back()->toValue() << std::endl;
    }
}


ARG_LIST_WRAPPER GOTO::loadArgumentString(std::string input_argument_string)
{
    std::string next_argument_string;
    bool is_argument_list;
    bool inside_parens;

    int nested_parens = 0;
    int index = 0;

    std::string non_list_expr;
    std::string list_expr;

    for (char &c : input_argument_string)
    {
        index++;
        if (inside_parens)
        {
            if (c == ')')
            {
                if (nested_parens == 0)
                {
                    if (is_argument_list)
                    {
                        next_argument_string.push_back(c);
                        std::cout << StringConstants::INFO_TAG << "Loaded GOTO list: " << next_argument_string << std::endl;
                        inside_parens = false;
                        is_argument_list = false;
                        list_expr = next_argument_string;
                        next_argument_string = "";
                        continue;
                    }
                    else
                    {
                        next_argument_string.push_back(c);
                        if (Globals::dump_parsed_values)
                        {
                            std::cout << StringConstants::INFO_TAG << "Loaded arithmetic argument string : " << next_argument_string << std::endl;
                        }
                        non_list_expr = next_argument_string;
                        inside_parens = false;
                        next_argument_string = "";
                        continue;
                    }
                }
                else
                {
                    nested_parens--;
                }
            }
            else if (c == '(')
            {
                nested_parens++;
            }
            else if (c == ')')
            {
                nested_parens--;
                next_argument_string.push_back(c);
            }
            else if (c == ',')
            {
                if (nested_parens != 0)
                {
                    std::cerr << StringConstants::ERROR_TAG << "Found list inside nested parenthesis. Was expecting either a list: (x,y,z) or an arithmetic expression: (a+b)." << std::endl;
                    ::printErrorLocation(index + 1, input_argument_string);
                    continue;
                }
                else
                {
                    is_argument_list = 1;
                }
            }
            next_argument_string.push_back(c);
        }
        else
        {
            if (c == ',')
            {
                // the end of a non list expression
                if (next_argument_string.length() != 0)
                {
                    non_list_expr = next_argument_string;
                    if (Globals::dump_parsed_values)
                    {
                        std::cout << StringConstants::INFO_TAG << "Loaded non-list GOTO expression: " << next_argument_string << std::endl;
                    }
                    next_argument_string = "";
                }
                else
                {
                    continue;
                }
            }
            else if (c == '(')
            {
                // a new expressioon
                inside_parens = true;
                next_argument_string.push_back(c);
            }
            else if (c == ')')
            {
                std::cerr << StringConstants::ERROR_TAG << "Found imbalanced parenthesis in GOTO statement: " << std::endl
                        << ::printErrorLocation(index + 1, input_argument_string) << std::endl;
            }
            else
            {
                next_argument_string.push_back(c);
            }
        }
    }

    if(next_argument_string.length() != 0){
        if(non_list_expr.length() != 0){
            std::cout << StringConstants::WARN_TAG << "Found two non-list string arguments - overwriting the first one. " << std::endl 
                << StringConstants::WARN_TAG << "First Argument: " << non_list_expr << std::endl
                << StringConstants::WARN_TAG << "Second Argument: " << next_argument_string << std::endl;
        } 

        if(Globals::dump_parsed_values){
            std::cout << StringConstants::INFO_TAG << "Loaded second argument " << next_argument_string << std::endl;
        }

        non_list_expr = next_argument_string;
    }

    return ARG_LIST_WRAPPER{list_expr, non_list_expr, !list_expr.empty()};
}

std::vector<TOC*> GOTO::generatetoc(std::string input){
    return {};
}