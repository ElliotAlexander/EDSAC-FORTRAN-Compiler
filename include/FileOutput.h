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
    bool dumpThreeOpCodeFile(std::vector<std::shared_ptr<ThreeOpCode> > input);
    bool dumpEDASCFile(std::vector<std::string> input);
}

#endif