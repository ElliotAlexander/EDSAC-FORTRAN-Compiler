#ifndef __FILE_OUTPUT_H_
#define __FILE_OUTPUT_H_

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>


#include "ThreeOpCode/ThreeOpCode.h"
#include "EDSAC.h"
#include "Globals.h"

namespace FileOutput {

    #define EDSAC_DEFAULT_FILE_OUTPUT std::string("out.edsac")

    #define THREE_OP_CODE_FILE_OUTPUT_PREFIX std::string("toc_")    // The prefix appended to three op code output files to differentiate them from edsac files.
    #define THREE_OP_CODE_DEFAULT_FILE_OUTPUT std::string("toc_out.edsac")
    
    bool dumpThreeOpCodeFile(std::vector<std::shared_ptr<ThreeOpCode> > input);
    bool dumpEDASCFile(std::vector<std::string> input);
}

#endif