#ifndef __EDSAC_H_
#define __EDSAC_H_

#include <vector>
#include <string>
#include "ThreeOpCode/ThreeOpCode.h"
namespace EDSAC
{
    std::vector<std::string> generateEDSAC(std::vector<std::shared_ptr<ThreeOpCode> > input, std::vector<std::string> libraries);
    std::string convertOperationEnumToString(THREE_OP_CODE_OPERATIONS op);
	std::string convert_int_to_edsac_op(int x);
} // EDSAC

#endif