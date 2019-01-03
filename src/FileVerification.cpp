#include "FileVerification.h"

bool FileVerification::verify(std::string str) {


    std::cout << "Verifying..." << std::endl;    
    bool return_val = true;
    /**
     *      Error Cases
     * */
    if(!verify_exists(str)){
        std::cerr << StringConstants::ERROR_TAG << "File not found: [" << str << "] - exiting...\n";
        return_val = false;
    }

    // Check the file is accessible.
    if (!verify_accessible(str)) {
        std::cerr << StringConstants::ERROR_TAG << "File " << str << " is not accessible, or is empty. Check your file permissions and try again.\n";
        return_val = false;
    } 
    
    if(!verify_regular_file(str)){
        std::cerr << StringConstants::ERROR_TAG << "File " << str << " does not appear to be a regular file.\n";
        return_val = false;
    }


    verify_extension(str);
    
    // Return
    return return_val;
}

bool FileVerification::verify_exists(std::string str){
    if(boost::filesystem::exists(str)){
        return true;
    } else {
        return false;
    };
}

bool FileVerification::verify_accessible(std::string str){
    std::ifstream filestream;
    filestream.open(str);
    if(filestream.is_open()){
        filestream.close();
        return true;
    } else {
        filestream.close();
        return false;
    }
}

bool FileVerification::verify_regular_file(std::string str){
    return boost::filesystem::is_regular_file(str);
}

bool FileVerification::verify_extension(std::string str){
    size_t i = str.rfind('.', str.length());
    if ((i != std::string::npos) && (!(Globals::allow_all_types))) {
        std::string x = str.substr(i+1, str.length() - i);
        auto b = MiscConstants::FILE_TYPE_WHITELIST;
        for(int j = 0; j < b->length(); j++){
            if(boost::iequals(x, b[j])) { 
                return true; 
            };
        }
        std::cerr << StringConstants::WARN_TAG << " File " << str << " has an unrecognised extension [" << x << "]. Use -x to disable these warnings.\n";
        return false;
    } else {
        return false;
    }

}