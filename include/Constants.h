#ifndef __CONSTS_H_INCLUDED
#define __CONSTS_H_INCLUDED

#include <string>

namespace StringConstants {
    const std::string INFO_TAG = "[INFO] ";
    const std::string ERROR_TAG = "[ERROR] ";
    const std::string WARN_TAG = "[WARN] ";
    const std::string EXCEPTION_TAG = "[EXCEPTION] ";
}


namespace MiscConstants {
    const std::string FILE_TYPE_WHITELIST[] = {"f", "for"};
}

namespace RegexConstants {
    const std::string INTEGER = "-?([0-9]+)";
    const std::string FLOATING_POINT = "-?[0-9]+(.[0-9]+)?";
    const std::string SUBROUTINE_NAME = "[A-Z]([0-9A-Z]+)?";
    const std::string VARIABLE_NAME = "[A-Z]([0-9A-Z]+)?";
    const std::string MULTI_VARIABLE_LIST = "([A-Z]([0-9A-Z]+)?(((,[A-Z]([0-9A-Z]+)?)?))+)?";
    const std::string ANY_ARG = "([0-9a-zA-Z\\.\\(\\)\\+\\*\\/\\^\\-])+";
    const std::string ANY_ARG_LIST = "([0-9a-zA-Z\\.\\(\\)\\+\\*\\/\\^\\-])+((,[0-9a-zA-Z.\\(\\)\\+\\*\\/\\^\\-]+)+)?";
};

#endif