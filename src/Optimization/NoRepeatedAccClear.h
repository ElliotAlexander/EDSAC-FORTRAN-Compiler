#ifndef __NO_REP_ACC_CLEAR_H_
#define __NO_REP_ACC_CLEAR_H_


#include <vector>
#include <string>
#include <memory>

#include "ThreeOpCode/ThreeOpCode.h"

struct NoRepeatedAccClearReturn {
    int skipped_lines;
    std::vector<std::shared_ptr<ThreeOpCode> > toc;
};

class NoRepeatedAccClear {
    public:
        NoRepeatedAccClear();
        NoRepeatedAccClearReturn processProgram(std::vector<std::shared_ptr<ThreeOpCode> > input);
};

#endif