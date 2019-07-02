#include "Logging.h"

/**
 * 
 *  Logging:
 *  
 * 
 *  This file offers an interface to a selection of pre_defined logging options. These broadly fall into two simple categories - conditional and unconditional.
 *  ConditionalMessages -> Log the message if the supplied boolean is true. This enablees single line "if this then that" logging.
 *  Unconditional messages only take an input, and format the message as required before outputting to the command line.
 *  Programatiicaly, the intention of this class is to allow easy, single access modification to log formatting, or to enable output to other formats easily, by modifying a single class.
 *  This file also offers a single point of contact with the command line - no messages should be outputted directly. This ensures that if a modification to how logging is implemented is required, it 
 *  can be done in a single point
 * 
 * This file also tracks the number of outputs in each category - INFO, WARN, and ERROR, and is responsible for generating the one line summary outted at the end of the file.
 *
 **/ 

namespace Logging {

    int info_count = 0;
    int warn_count = 0;
    int error_count = 0;

    void logConditionalErrorMessage(bool conditional, std::string input_text){
        if(conditional) {
            error_count++;
            std::cerr << StringConstants::ERROR_TAG << input_text << std::endl;
        }
    }

    void logConditionalInfoMessage(bool conditional, std::string input_text){
        if(conditional){
            info_count++;
            std::cout << StringConstants::INFO_TAG << input_text << std::endl;
        }
    }

    void logConditionalMessage(bool conditional, std::string input){
        if(conditional){
            std::cout << input << std::endl;
        }
    }

    void logConditionalWarnMessage(bool conditional, std::string input){
        if(conditional){
            warn_count++;
            std::cout << StringConstants::WARN_TAG << input << std::endl;
        }
    }

    void logErrorMessage(std::string input_text){
        error_count++;
        std::cerr << StringConstants::ERROR_TAG << input_text << std::endl;
    } 



    void logInfoMessage(std::string input_text){
        info_count++;
        std::cout << StringConstants::INFO_TAG << input_text << std::endl;
    }

    void logMessage(std::string input){
        std::cout << input << std::endl;
    }

    void logNewLine(){
        std::cout << std::endl << std::endl;
    }


    // This function generates the summary outpu, called at the end of runtime
    void logOutputSummary(){
        std::cout << "\nOutput Summary:\n"
        << "Finished with " << error_count << " errors, " << warn_count << " warnings and " << info_count << " info messages."
        << std::endl;
    }

    void logWarnMessage(std::string input){
        warn_count++;
        std::cout << StringConstants::WARN_TAG << input << std::endl;
    }
}


void testMethod(){
    std::cout << "Test" << std::endl;
}