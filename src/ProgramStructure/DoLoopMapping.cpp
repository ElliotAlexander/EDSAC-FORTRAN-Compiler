#include "ProgramStructure/DoLoopMapping.h"

namespace DoLoopMapping {
	std::vector <DO_LOOP_ENTRY> do_mappings;


	bool addDoLoopMapping(int line_label, std::shared_ptr<int> line_mapping) {
		DO_LOOP_ENTRY x{
			line_label,
			line_mapping
		};

		Logging::logInfoMessage("Adding DO loop mapping for " + std::to_string(line_label));
		do_mappings.push_back(x);
		return true;
	}


	DO_LOOP_RETURN_VALUE retrieveDoLoopMapping(std::string line_label) {
		if (do_mappings.empty()) {
			return { false, nullptr };
		}
		else {
			if (::stripWhitespaceString(line_label).empty()) {
				return { false, nullptr };
			}
			for (std::vector<DO_LOOP_ENTRY>::iterator it = do_mappings.begin(); it != do_mappings.end(); ++it) {
				if ((*it).line_label == std::stoi(line_label)) {
					return { true, (*it).return_line_mapping };
				}
			}
			return { false, nullptr };
		}
	}
};
