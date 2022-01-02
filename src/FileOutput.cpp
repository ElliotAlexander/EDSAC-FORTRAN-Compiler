#include "FileOutput.h"

/**
 *  FileOutput contains the relevant utility classes for generating all OUTPUT files.
 *  Note that this does not encompass file inputs - the majority of which are handled inside FileContainer, FileVerification and Main.cpp
 **/ 

namespace FileOutput {

    // bool dumpEDASCFile(std::vector<std::string> input)
    // 
    // @param std::vector<std::string> input -> The input string to be outputted to the file.
    // @return bool -> Success indicator to the calling class
    //
    // This function takes a list of EDSAC instructions, formatted as a string, and outputs them to a file
    // This file can be specified by the user via a command argument, else it outputs to a default name.
    bool dumpEDASCFile(std::vector<std::string> input){
        std::ofstream output_file;                              // Setup an output file stream
        // If the user has set an output file name - use that. Else, use a default
        std::string file_name = Globals::output_file_set ? Globals::output_file : EDSAC_DEFAULT_FILE_OUTPUT;     
        output_file.open(file_name);
        Logging::logInfoMessage("Writing EDSAC output to " + file_name);
        for(std::vector<std::string>::iterator it = input.begin(); it != input.end(); ++it){             
            // Pipe that line + an end character to the file.       
            output_file << (*it) << std::endl;                          
            // EoL characters are ignored by the simulator, so this is fine.                                        
        }                                                                                                       
        output_file.close();                                                                                 
        Logging::logInfoMessage("Finished writing " + file_name);
        return true;
    }
    
    /** bool dumpThreeOpCodeFile(std::vector<std::shared_ptr<ThreeOpCode> > input)
    *
    * @param std::vector<std::shared_ptr<ThreeOpCode> > input -> An input list of the compelte program body, 
    * including symbol tables, as Three Op Code (an internal representation)
    * @return bool -> Success / failure to the calling class.
    *
    * This function takes an internal representation of the program as three op code, and outputs it to a file.
    * THis  involves opening a file, generating a string for each ThreeOpCode instruction, and then outputting too and closing the file.
    *
    *  This function may exit immediately if the -c/--threeopcode argumeent is not enabled.
    **/
    bool dumpThreeOpCodeFile(std::vector<std::shared_ptr<ThreeOpCode> > input){

        // This function is always called, but only activates when a command argumment is set.
        // Check that commmand argument.
        if(!Globals::dump_three_op_code){
            Logging::logInfoMessage("Skipping file output for Three Op Code - dump_three_op_code is disabled.");
            return true;
        } else {
            std::ofstream output_file;
            // If the user has specified an output file name, use that. Else use the default file name.
            std::string file_name = Globals::output_file_set ? THREE_OP_CODE_FILE_OUTPUT_PREFIX + Globals::output_file : THREE_OP_CODE_DEFAULT_FILE_OUTPUT;        
            output_file.open(file_name);                                                                                       
            Logging::logInfoMessage("Writing Three Op Code output to " + file_name);
            //  Iterate through each line of the input list
            for(std::vector<std::shared_ptr<ThreeOpCode> >::iterator it = input.begin(); it != input.end(); ++it){              
                 // Call utility method printToString to output three op code to string. Add this to the file
                output_file << (*it)->printToString() << std::endl;                                                            
            }
            output_file.close();                                                                                               
            Logging::logInfoMessage("Finished writing " + file_name);
            return true;
        }
    }
}
