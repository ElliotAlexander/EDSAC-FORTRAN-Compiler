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
		// This might contain multiple do loops
		// do_mappings is a FIFO - effectively. 
		std::vector<std::shared_ptr<ThreeOpCode> > do_loop_return_inject;
		if (do_mappings.empty()) {
			return { false, {} };
		}
		else {
			if (::stripWhitespaceString(line_label).empty()) {
				return { false, {} };
			}
			for (std::vector<DO_LOOP_ENTRY>::reverse_iterator it = do_mappings.rbegin(); it != do_mappings.rend(); ++it) {

				// A temporary reference is required in order to maintain the correct offset.
				if ((*it).line_label == std::stoi(line_label)) {
					Logging::logMessage("Found line return ");
					int new_val = *it->exit_line_mapping + end_line_mapping + do_loop_return_inject.size();
					*it->exit_line_mapping = new_val;
					do_loop_return_inject.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("0", THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
                    do_loop_return_inject.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode((*it).return_line_mapping, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_POSTITIVE, false)));
				}
			}
			return { true,  do_loop_return_inject };
		}
	}
};
