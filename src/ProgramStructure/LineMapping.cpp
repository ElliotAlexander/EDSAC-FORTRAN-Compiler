#include "ProgramStructure/LineMapping.h"

namespace LineMapping {

    bool addLineMapping(std::string line_label, int memory_address){
        // Remove whitespace so we can accurately compare lengths.
        line_label = ::stripWhitespaceString(line_label);
        int line_label_int;
        if(!line_label.empty()){
            line_label_int = std::stoi(line_label, nullptr, 10);
            int line_label_length_test = line_label_int;
            unsigned int number_of_digits = 0;
            int base = 10;

            do {
                ++number_of_digits; 
                line_label_length_test /= base;
            } while (line_label_length_test);
            
            if(number_of_digits != line_label.length()){
                Logging::logWarnMessage("Warning - digits have been lost from line " + line_label);
            }

            std::map<int, std::shared_ptr<int> >::iterator it = line_mappings.find(line_label_int);
            int entry;
            if(it != LineMapping::line_mappings.end())
            {
				if (*(it->second) == -1) {
					Logging::logInfoMessage("Found temporary reference to line " + line_label + ". Replacing with a new Memory Address of " + std::to_string(memory_address));
					*(it->second) = memory_address;
					return true;
				}
				else {
					Logging::logInfoMessage("Warning - line " + line_label + " already exists as address " + std::to_string(*(it->second)));
					return false;
				}
            } else {
				Logging::logInfoMessage("Line " + std::to_string(line_label_int) + " doesn't exist, adding a temporary reference.");
				line_mappings.insert(std::map<int, std::shared_ptr<int> > ::value_type(line_label_int, std::make_shared<int>(memory_address)));
				return true;
            }
        } else {
            return true;
        }

    }

    std::shared_ptr<int> retrieveLineMapping(int line){
        std::map<int, std::shared_ptr<int> >::iterator it = line_mappings.find(line);
        int entry;
        if(it != LineMapping::line_mappings.end()) {
            return it->second;
        } else {
            Logging::logErrorMessage("Failed to retrieve line mapping for " + std::to_string(line));
			line_mappings.insert(std::map<int, std::shared_ptr<int> >::value_type(line, std::make_shared<int>(-1)));
			return retrieveLineMapping(line);
        }
    }
}


