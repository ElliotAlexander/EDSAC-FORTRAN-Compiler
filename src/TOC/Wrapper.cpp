#include "ArithmeticParser/Wrapper.h"

Wrapper::Wrapper(TOC *in)
{
    tt = TOC_TYPES::VARIABLE_E;
    in_save = in; 
}

std::vector<std::string> Wrapper::toTOCStr(int &variable_index)
{
    std::vector<std::string> x = in_save->toTOCStr(variable_index);
    return x;
}

std::string Wrapper::toValue()
{
    std::string x = in_save->toValue();
    return x;
}