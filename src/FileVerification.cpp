#include "FileVerification.h"

// bool FileVerification::verify(std::string file_input);
//
// @param std::string file_input -> The name of the input file
// @return bool -> success of failure flag
//
// This function takes the name of a not yet loaded file, and verifies several properties about the file prior to loading the file into the program.
// This includes verifying that the file exists, it can be opened, it is a text file and it has the correct extensions.
// This function is the only public method in the class - all other methods are private helper methods for this function.
//
FILE_VERIFICATION_SUCCESS_FLAG FileVerification::verify(std::string file_input) {
    if(!verify_exists(file_input)){     // If the file does not exist, exit here.
        Logging::logErrorMessage("File not found: [" + file_input + "] - exiting...");
        return false;
    } else if (!verify_accessible(file_input)) {    // if rthe file is not accessible - exit here.
        Logging::logErrorMessage("File " + file_input + " is not accessible, or is empty. Check your file permissions and try again.");
        return false;
    } else if(!verify_regular_file(file_input)){    // If the file is not regular (i.e. not a text file), exit here.
        Logging::logErrorMessage("File " + file_input + " does not appear to be a regular file.");
        return false;
    } else {
        verify_extension(file_input);               // If the file is not an extension we recognise - warn the user. NOte that this check does not exit.
        return true;
    }
}


// FILE_VERIFICATION_SUCCESS_FLAG FileVerification::verify_accessible(std::string file_input)
// 
// @param file_input - The name of the input file to be verified
// 
// This function takes an input, and returns a success / failure flag depending on whether the input file name is accessible.
// If the file in not accessible, the function exits with false.
FILE_VERIFICATION_SUCCESS_FLAG FileVerification::verify_accessible(std::string file_input){
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


// FILE_VERIFICATION_SUCCESS_FLAG FileVerification::verify_exists(std::string file_input){
// 
// @param file_input - The name of the input file to be verified.
// 
// This function takes an input file name and verifies that it exists in the current path. 
// If the file is not found - return false.
FILE_VERIFICATION_SUCCESS_FLAG FileVerification::verify_exists(std::string file_input){
    return boost::filesystem::exists(file_input) ? true : false;
}



// void FileVerification::verify_extension(std::string file_input){
// 
// @param file_input - The name of the input file to be verified.
// 
// This function takes an input file name, and verifies that it's extension is compatiable.
// Note that this check can be disabled via Globals::allow_all_types.
// Note that this function is not blocking - only a warning is generated if an invalid file eextension is found.
bool FileVerification::verify_extension(std::string file_input){
    size_t i = file_input.rfind('.', file_input.length());                  // Jump to the last instance of a dot in the file name. 
    if ((i != std::string::npos) && (!(Globals::allow_all_types))) {        // If the file has an extension after the dot, and this check is enabled    
        std::string x = file_input.substr(i+1, file_input.length() - i);    // Build up a string of the file extension, not including the dot. 
        auto b = MiscConstants::FILE_TYPE_WHITELIST;                        // 
        for(int j = 0; j < b->length(); j++){                               // Iterate through the allowed file extensions, and return true if we get a match. 
            if(x == b[j]) {                                   // If we don't find a matching file extension, return false. Note that
                return true; 
            };
        }
        Logging::logWarnMessage(" File " + file_input + " has an unrecognised extension [" + x + "]. Use -x to disable these warnings.");
    }
    return false;
}



// FILE_VERIFICATION_SUCCESS_FLAG FileVerification::verify_regular_file(std::string file_input){
// 
// @param file_input - The name of the input file to be verified.
// 
// This function takes an input file name, and verifies that the file is a text file.
FILE_VERIFICATION_SUCCESS_FLAG FileVerification::verify_regular_file(std::string file_input){
    return boost::filesystem::is_regular_file(file_input);
}

