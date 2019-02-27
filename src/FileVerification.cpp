#include "FileVerification.h"

bool FileVerification::verify(std::string file_input) {


    bool return_val = true;
    /**
     *      Error Cases
     * */
    if(!verify_exists(file_input)){
        Logging::logErrorMessage("File not found: [" + file_input + "] - exiting...");
        return_val = false;
    }

    // Check the file is accessible.
    if (!verify_accessible(file_input)) {
        Logging::logErrorMessage("File " + file_input + " is not accessible, or is empty. Check your file permissions and try again.");
        return_val = false;
    } 
    
    if(!verify_regular_file(file_input)){
        Logging::logErrorMessage("File " + file_input + " does not appear to be a regular file.");
        return_val = false;
    }


    verify_extension(file_input);
    
    // Return
    return return_val;
}

bool FileVerification::verify_exists(std::string file_input){
    if(boost::filesystem::exists(file_input)){
        return true;
    } else {
        return false;
    };
}

bool FileVerification::verify_accessible(std::string file_input){
    std::ifstream filestream;
    filestream.open(file_input);
    if(filestream.is_open()){
        filestream.close();
        return true;
    } else {
        filestream.close();
        return false;
    }
}

bool FileVerification::verify_regular_file(std::string file_input){
    return boost::filesystem::is_regular_file(file_input);
}

bool FileVerification::verify_extension(std::string file_input){
    size_t i = file_input.rfind('.', file_input.length());
    if ((i != std::string::npos) && (!(Globals::allow_all_types))) {
        std::string x = file_input.substr(i+1, file_input.length() - i);
        auto b = MiscConstants::FILE_TYPE_WHITELIST;
        for(int j = 0; j < b->length(); j++){
            if(boost::iequals(x, b[j])) { 
                return true; 
            };
        }
        Logging::logWarnMessage(" File " + file_input + " has an unrecognised extension [" + x + "]. Use -x to disable these warnings.");
        return false;
    } else {
        return false;
    }

}