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

#endif