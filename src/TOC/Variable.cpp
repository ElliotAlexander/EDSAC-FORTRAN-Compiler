#include "ArithmeticParser/Variable.h"

Variable::Variable(char *name_in)
{
    tt = TOC_TYPES::VARIABLE_E;
    name = name_in;
}

std::vector<std::string> Variable::toTOCStr(int &variable_index)
{
    std::vector<std::string> x;
    x.push_back(std::string("$" + std::to_string(variable_index) + "=" + name));
    variable_index++;
    return x;
}

std::string Variable::toValue()
{
    std::string x = name;
    return x;
}