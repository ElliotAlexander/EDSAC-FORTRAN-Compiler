#include "ArithmeticParser/Variable.h"

Variable::Variable(char *name_in)
{
    tt = TOC_TYPES::VARIABLE_E;
    name = name_in;
}

TOC_RETURN_VALUE Variable::generateThreeOPCode(int &variable_index){
    if(memory_mapped){
        return {std::vector<std::string>{}, std::string('$' + std::to_string(memory_mapping))};
    } else {
        std::vector<std::string> pre_string;
        pre_string.push_back(std::string("$" + std::to_string(variable_index) + "=" + Variable::name));
        std::string call_value = std::string("$" + std::to_string(variable_index));
        variable_index += 1;
        return {pre_string, call_value};
    }
}