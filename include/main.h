#ifndef __MAIN_H_INCLUDED
#define __MAIN_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>  
#include <time.h>
#include <boost/format.hpp>
#include <algorithm>    // std::sort
#include <string>


#include "Logging.h"
#include "Constants.h"
#include "CommandArgs.h"
#include "FileVerification.h"
#include "FileContainer.h"
#include "Globals.h"
#include "Utils.h"
#include "ThreeOpCode/ThreeOpCode.h"
#include "ProgramStructure/FunctionMapping.h"
#include "ProgramStructure/LineMapping.h"
#include "Optimization/NoRepeatedAccClear.h"
#include "FileOutput.h"
#include "EDSAC.h"
#include "StandardLibrary/LibraryBuilder.h"
#include "ProgramStructure/DoLoopMapping.h"


#define PROGRAM_ERROR_EXIT_VALUE -1
#define PROGRAM_LINE_MAPPING_RAW_OFFSET 1
#define PROGRAM_START_THREE_OP_CODE std::vector<std::shared_ptr<ThreeOpCode> >{ \
	std::shared_ptr<ThreeOpCode>(new ThreeOpCode("", THREE_OP_CODE_OPERATIONS::STOP_PROGRAM, false)), \
	std::shared_ptr<ThreeOpCode>(new ThreeOpCode("", THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_NEGATIVE, std::string("K"))) \
}


#endif