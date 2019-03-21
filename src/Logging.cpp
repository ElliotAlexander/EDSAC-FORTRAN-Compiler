#include "Logging.h"

namespace Logging {

    int info_count = 0;
    int warn_count = 0;
    int error_count = 0;

    void logErrorMessage(std::string input_text){
        error_count++;
        std::cerr << StringConstants::ERROR_TAG << input_text << std::endl;
    } 

    void logConditionalErrorMessage(bool conditional, std::string input_text){
        if(conditional) {
            error_count++;
            std::cerr << StringConstants::ERROR_TAG << input_text << std::endl;
        }
    }


    void logInfoMessage(std::string input_text){
        info_count++;
        std::cout << StringConstants::INFO_TAG << input_text << std::endl;
    }

    void logConditionalInfoMessage(bool conditional, std::string input_text){
        if(conditional){
            info_count++;
            std::cout << StringConstants::INFO_TAG << input_text << std::endl;
        }
    }

    void logWarnMessage(std::string input){
        warn_count++;
        std::cout << StringConstants::WARN_TAG << input << std::endl;
    }

    void logConditionalWarnMessage(bool conditional, std::string input){
        if(conditional){
            warn_count++;
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

    void logOutputSummary(){
        std::cout << "\nOutput Summary:\n"
        << "Finished with " << error_count << " errors, " << warn_count << " warnings and " << info_count << " info messages."
        << std::endl;
    }

}