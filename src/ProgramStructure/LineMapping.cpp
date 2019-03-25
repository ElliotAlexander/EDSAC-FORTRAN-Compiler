#include "ProgramStructure/LineMapping.h"

namespace LineMapping {

    std::map<int, std::shared_ptr<int>> line_mappings;
    std::vector<std::shared_ptr<int>> temporary_line_mappings;

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
					Logging::logConditionalInfoMessage(Globals::output_line_mappings, "Found temporary reference to line " + line_label + ". Replacing with a new Memory Address of " + std::to_string(memory_address));
					*(it->second) = memory_address;
					return true;
				}
				else {
					Logging::logConditionalInfoMessage(Globals::output_line_mappings, "Warning - line " + line_label + " already exists as address " + std::to_string(*(it->second)));
					return false;
				}
            } else {
				Logging::logConditionalInfoMessage(Globals::output_line_mappings, "Line " + std::to_string(line_label_int) + " doesn't exist, adding a temporary reference.");
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
            Logging::logWarnMessage("Failed to retrieve line mapping for " + std::to_string(line));
			line_mappings.insert(std::map<int, std::shared_ptr<int> >::value_type(line, std::make_shared<int>(-1)));
			return retrieveLineMapping(line);
        }
    }


    bool offsetLineMapping(int offset){
        Logging::logConditionalMessage(Globals::output_line_mappings, "\n\n:: Line Mapping Transformations :: \n\n");
        for(std::map<int, std::shared_ptr<int> >::iterator it = line_mappings.begin(); it != line_mappings.end(); ++it){
            int new_val = *it->second.get() + offset;
            *it->second = new_val;
            Logging::logConditionalMessage(Globals::output_line_mappings, "Applying Line Mapping Offset of " + std::to_string(offset) + " to " + std::to_string(*it->second));
        }

        Logging::logConditionalInfoMessage(Globals::output_line_mappings, " - Temporary Line Mapping transformations - ");

        for(int index = 0; index < temporary_line_mappings.size(); index++){
            int new_value = (*temporary_line_mappings.at(index)) + offset;
            (*temporary_line_mappings.at(index)) = new_value;
            Logging::logConditionalInfoMessage(Globals::output_line_mappings, "Applying Line Mapping Offset of " + std::to_string(offset) + " to " + std::to_string(new_value));
        }

        Logging::logConditionalMessage(Globals::output_line_mappings, "\n --- End Line Mapping Transformations --- \n\n");
        return true;
    }

    std::shared_ptr<int> addTemporaryLineMapping(int input){
        Logging::logConditionalInfoMessage(Globals::output_line_mappings, "Adding temporary line mapping for line " + std::to_string(input));
        std::shared_ptr<int> ptr = std::make_shared<int>(input);
        temporary_line_mappings.push_back(ptr);
        return ptr;
    }
}


