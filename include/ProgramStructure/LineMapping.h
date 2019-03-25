#ifndef __LINE_MAPPING_H_
#define __LINE_MAPPING_H_

#include <map>
#include <string>
#include <memory>
#include "Utils.h"

#include "Logging.h"

namespace LineMapping {
    bool addLineMapping(std::string, int);
    std::shared_ptr<int> retrieveLineMapping(int);
    bool offsetLineMapping(int offset);
    std::shared_ptr<int> addTemporaryLineMapping(int);
    extern std::map<int, std::shared_ptr<int>> line_mappings;
    extern std::vector<std::shared_ptr<int> > temporary_line_mappings;
}

#endif