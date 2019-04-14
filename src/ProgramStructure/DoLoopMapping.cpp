#include "ProgramStructure/DoLoopMapping.h"

namespace DoLoopMapping {
	std::vector <DO_LOOP_ENTRY> do_mappings;


	std::shared_ptr<int> addDoLoopMapping(int line_label, std::shared_ptr<int> line_mapping) {
		DO_LOOP_ENTRY x{
			line_label,
			line_mapping,
			LineMapping::addTemporaryLineMapping(0)
		};

		Logging::logInfoMessage("Adding DO loop mapping for " + std::to_string(line_label));
		Logging::logInfoMessage("Adding temporary line reference for loop end at " + std::to_string(line_label));
		do_mappings.push_back(x);
		return x.exit_line_mapping;
	}


	DO_LOOP_RETURN_VALUE retrieveDoLoopMapping(std::string line_label, int end_line_mapping) {
		if (do_mappings.empty()) {
			return { false, nullptr };
		}
		else {
			if (::stripWhitespaceString(line_label).empty()) {
				return { false, nullptr };
			}
			for (std::vector<DO_LOOP_ENTRY>::iterator it = do_mappings.begin(); it != do_mappings.end(); ++it) {

				// A temporary reference is required in order to maintain the correct offset.
				if ((*it).line_label == std::stoi(line_label)) {
					int new_val = *it->exit_line_mapping + end_line_mapping;
					*it->exit_line_mapping = new_val;
					return { true, (*it).return_line_mapping };
				}
			}
			return { false, nullptr };
		}
	}
};
