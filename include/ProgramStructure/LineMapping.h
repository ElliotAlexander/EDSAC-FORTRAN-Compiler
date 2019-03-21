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
    static std::map<int, std::shared_ptr<int>> line_mappings;
}

#endif