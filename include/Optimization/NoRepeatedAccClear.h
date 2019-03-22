#ifndef __NO_REP_ACC_CLEAR_H_
#define __NO_REP_ACC_CLEAR_H_


#include <vector>
#include <string>
#include <memory>

#include "ThreeOpCode/ThreeOpCode.h"

class NoRepeatedAccClear {
    public:
        NoRepeatedAccClear();
        std::vector<std::shared_ptr<ThreeOpCode> > processProgram(std::vector<std::shared_ptr<ThreeOpCode> > input);
};

#endif