#include "ProgramStructure/LineMapping.h"

namespace LineMapping {


/**
 * 
 *  This namespace is responsible for mapping integer values to line references.
 *  Line mappings and temporary line mappings are stored in this namespace, this maps an in to a changing line mapping value.
 *  
 *  These line mappings may be changed at any point, and the calling fucntion on each method becomes respoknsible for handling a pointer to the entry.
 * 
 * 
 **/ 


    std::map<int, std::shared_ptr<int>> line_mappings;      // this variable stores the fixed line mappings
    std::vector<std::shared_ptr<int>> temporary_line_mappings;      // temporary line mappings are functionally identical, however
    // are only ever returned by reference. The calling function is entirely responsible for handling these references.


/**
 * 
 *     bool addLineMapping(std::string line_label, int memory_address)
 * 
 * 
 *  This function is responsible for adding line mappings.
 *  Inputs:
 *      std::string line_label -> the string value of the line label. This is converted to an int within this class.
 *      int memory_address -> The starting address of the line mapping.
 * 
 * */
    bool addLineMapping(std::string line_label, int memory_address){
        // Remove whitespace so we can accurately compare lengths.
        line_label = ::stripWhitespaceString(line_label);

        /**
         * 
         * This function strips whitespace, and ensurees that the line mapping is properly convereted to an integer.
         * This is defensive programming - any line mapping that isn't an intger should already have been caught. 
         * 
         **/ 
        int line_label_int;
        if(!line_label.empty()){
            line_label_int = std::stoi(line_label, nullptr, 10);

            /**
             * 
             * This algorithm ensures that the lenght of the line label hasnt changed
             * i.e. it has been converted to an int correctly.
             * 
             **/ 

            int line_label_length_test = line_label_int;
            unsigned int number_of_digits = 0;
            int base = 10;

            do {
                ++number_of_digits; 
                line_label_length_test /= base;
            } while (line_label_length_test);
            


            // If the length has changed
            // Warn the user.
            if(number_of_digits != line_label.length()){
                Logging::logWarnMessage("Warning - digits have been lost from line " + line_label);
            }


            /**
             * 
             * This  sectionof code iterates through each line mapping
             * 
             * 
             **/ 
            std::map<int, std::shared_ptr<int> >::iterator it = line_mappings.find(line_label_int);
            int entry;

            // Iterate through all line mappings,
            // iuf we find the correct line mapping
            if(it != LineMapping::line_mappings.end())
            {

                // If the line mapping is set to zero
                // It's value is considered temporary.
                // this will be offset later
				if (*(it->second) == -1) {
					Logging::logConditionalInfoMessage(Globals::output_line_mappings, "Found temporary reference to line " + line_label + ". Replacing with a new Memory Address of " + std::to_string(memory_address));
					*(it->second) = memory_address;
					return true;
				} else {

                    // warn the user that we're overwriting the line mapping.
                    // Thbis is rarely a bad idea
					Logging::logConditionalInfoMessage(Globals::output_line_mappings, "Warning - line " + line_label + " already exists as address " + std::to_string(*(it->second)));
					return false;
				}
            } else {
                // the line mapping isn't found
                // If the line mapping isn't found, return a temporary line mapping.
                // This is essneitla for forward declarations of line mappings - i..e when a user references a line ahead of program flow.
				Logging::logConditionalInfoMessage(Globals::output_line_mappings, "Line " + std::to_string(line_label_int) + " doesn't exist, adding a temporary reference.");
				line_mappings.insert(std::map<int, std::shared_ptr<int> > ::value_type(line_label_int, std::make_shared<int>(memory_address)));
				return true;
            }
        } else {
            return true;
        }
    }


/**
 * 
 *     LineMappingReturn retrieveLineMapping(int line) 
 *  
 *      This method is the accessor for line mapping.
 *      
 * 
 **/ 
    LineMappingReturn retrieveLineMapping(int line){
        std::map<int, std::shared_ptr<int> >::iterator it = line_mappings.find(line);
        int entry;
        if(it != LineMapping::line_mappings.end()) {
            return { true, it->second };
        } else {
            Logging::logWarnMessage("Failed to retrieve line mapping for " + std::to_string(line));
            Logging::logWarnMessage("This may be indicative of an invalid line label, or a reference to an non-existent line label.");
			line_mappings.insert(std::map<int, std::shared_ptr<int> >::value_type(line, std::make_shared<int>(-1)));
			return retrieveLineMapping(line);
        }
    }



/**
 * 
 *     bool offsetLineMapping(int offset)
 * 
 * This function is responsible for offsetting all line mappings.
 * Line mappings are held in three op code as arguments, and once offset are considered final.
 * 
 * This function is responsible for hadling this offset, and for informing the user.
 * The return value is constant, and is able to be disregarded.
 * 
 * */
    bool offsetLineMapping(int offset){
        Logging::logConditionalMessage(Globals::output_line_mappings, "\n\n:: Line Mapping Transformations :: \n\n");
        for(std::map<int, std::shared_ptr<int> >::iterator it = line_mappings.begin(); it != line_mappings.end(); ++it){
            int new_val = *it->second.get() + offset;
            *it->second = new_val;
            Logging::logConditionalMessage(Globals::output_line_mappings, "Applying Line Mapping Offset of " + std::to_string(offset) + " to " + std::to_string(*it->second));
        }

        Logging::logConditionalMessage(Globals::output_line_mappings, "\n --- Temporary Line Mapping transformations ---\n ");

        for(int index = 0; index < temporary_line_mappings.size(); index++){
            int new_value = (*temporary_line_mappings.at(index)) + offset;
            Logging::logConditionalMessage(Globals::output_line_mappings, "Applying Line Mapping Offset of " + std::to_string(offset) + " to " + std::to_string((*temporary_line_mappings.at(index))) + " to " + std::to_string(offset));
            (*temporary_line_mappings.at(index)) = new_value;
        }

        Logging::logConditionalMessage(Globals::output_line_mappings, "\n\n --- End Line Mapping Transformations --- \n\n");
        return true;
    }

/**
 * 
 * This function is responsible for adding temporary line mappings.
 * 
 * Temporary line mappings cannot be retrieved, and can only be accessed by reference.
 * 
 **/ 
    std::shared_ptr<int> addTemporaryLineMapping(int input){
        Logging::logConditionalInfoMessage(Globals::output_line_mappings, "Adding temporary line mapping for line " + std::to_string(input));
        std::shared_ptr<int> ptr = std::make_shared<int>(input);
        temporary_line_mappings.push_back(ptr);
        return ptr;
    }
}


