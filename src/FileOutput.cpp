#include "FileOutput.h"


namespace FileOutput {
    
    bool dumpThreeOpCodeFile(std::vector<std::shared_ptr<ThreeOpCode> > input){

        if(!Globals::dump_three_op_code){
            Logging::logInfoMessage("Skipping file output for Three Op Code - dump_three_op_code is disabled.");
            return true;
        }
        
        std::ofstream output_file;
        std::string file_name = Globals::output_file_set ? std::string("toc_") + Globals::output_file : std::string("toc_out.edsac");
        output_file.open(file_name);
        Logging::logInfoMessage("Writing Three Op Code output to " + file_name);
        for(std::vector<std::shared_ptr<ThreeOpCode> >::iterator it = input.begin(); it != input.end(); ++it){
            output_file << (*it)->printToString() << std::endl;
        }
        output_file.close();
        Logging::logInfoMessage("Finished writing " + file_name);
        return true;
    }


    bool dumpEDASCFile(std::vector<std::string> input){



        std::ofstream output_file;
        std::string file_name = Globals::output_file_set ? Globals::output_file : std::string("out.edsac");
        output_file.open(file_name);
        Logging::logInfoMessage("Writing EDSAC output to " + file_name);
        for(std::vector<std::string>::iterator it = input.begin(); it != input.end(); ++it){
            // no newline for edsac codes
            output_file << (*it) << std::endl;
        }
        output_file.close();
        Logging::logInfoMessage("Finished writing " + file_name);
        return true;
    }
}
