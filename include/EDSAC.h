#ifndef __EDSAC_H_
#define __EDSAC_H_

#include <vector>
#include "ThreeOpCode/ThreeOpCode.h"
namespace EDSAC
{
    std::vector<std::string> generateEDSAC(std::vector<std::shared_ptr<ThreeOpCode> > input);
    std::string convertOperationEnumToString(THREE_OP_CODE_OPERATIONS op);
} // EDSAC

#endif