#include "Logging.h"

namespace Logging {

    void logErrorMessage(std::string input_text){
        std::cerr << StringConstants::ERROR_TAG << input_text << std::endl;
    } 

    void logConditionalErrorMessage(bool conditional, std::string input_text){
        if(conditional) {
            std::cerr << StringConstants::ERROR_TAG << input_text << std::endl;
        }
    }


    void logInfoMessage(std::string input_text){
        std::cout << StringConstants::INFO_TAG << input_text << std::endl;
    }

    void logConditionalInfoMessage(bool conditional, std::string input_text){
        if(conditional){
            std::cout << StringConstants::INFO_TAG << input_text << std::endl;
        }
    }

    void logWarnMessage(std::string input){
        std::cout << StringConstants::WARN_TAG << input << std::endl;
    }

    void logConditionalWarnMessage(bool conditional, std::string input){
        if(conditional){
            std::cout << StringConstants::WARN_TAG << input << std::endl;
        }
    }

    void logNewLine(){
        std::cout << std::endl << std::endl;
    }

    void logMessage(std::string input){
        std::cout << input << std::endl;
    }

    void logConditionalMessage(bool conditional, std::string input){
        if(conditional){
            std::cout << input << std::endl;
        }
    }

}