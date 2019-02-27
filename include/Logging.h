#ifndef __LOGGING_H_DEFINED
#define __LOGGING_H_DEFINED

#include <string>
#include <iostream>

#include "Constants.h"

namespace Logging {
    void logErrorMessage(std::string input_text);
    void logConditionalErrorMessage(bool conditional, std::string input_text);
    void logInfoMessage(std::string input_text);
    void logConditionalInfoMessage(bool conditional, std::string input_text);
    void logMessage(std::string input);
    void logConditionalMessage(bool conditional, std::string input);
    void logWarnMessage(std::string input);
    void logConditionalWarnMessage(bool conditional, std::string input);
    void logNewLine();
}

#endif