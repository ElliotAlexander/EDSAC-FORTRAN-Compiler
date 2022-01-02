#ifndef __LINE_MAPPING_H_
#define __LINE_MAPPING_H_

#include <map>
#include <string>
#include <memory>
#include "Utils.h"

#include "Logging.h"

namespace LineMapping {

    struct LineMappingReturn{
        bool result;
        std::shared_ptr<int> value;
    };

    bool addLineMapping(std::string, int);
    LineMappingReturn retrieveLineMapping(int);
    bool offsetLineMapping(int offset);
    std::shared_ptr<int> addTemporaryLineMapping(int);
    extern std::map<int, std::shared_ptr<int>> line_mappings;
    extern std::vector<std::shared_ptr<int> > temporary_line_mappings;
}

#endif