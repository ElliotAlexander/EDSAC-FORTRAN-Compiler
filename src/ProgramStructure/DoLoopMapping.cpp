#include "ProgramStructure/DoLoopMapping.h"

/**
 * 
 * 	This namespace encapsulates the methods required for DO loops
 * 	It exists to keep the global namespace clean.
 * 	This namespace also encapsulates do_mappings, keeping it out of the global space.
 * 
 * 
 * 	These functions are referenced from across the program, so using a class isn't an option.
 * 
 **/ 

namespace DoLoopMapping {

	// This Represents the complete list of DOO loop's in the program.
	std::vector <DO_LOOP_ENTRY> do_mappings;


	/**
	 * 
	 * 	std::shared_ptr<int> addDoLoopMapping(int line_label, std::shared_ptr<int> line_mapping)
	 * 
	 * Inputs:
	 * 		line_label -> the integer line label that the DO loop terminates on.
	 * 		line_mapping -> The starting line, i.e. the point the DO loop should jump back to when it loops. (The top of the loop)
	 * 
	 * 	This method constructs an entry for the do loop, and is called when the prgoram sees a DO token. 
	 * 	This entry is later used to check each line for a do loop mapping. 
	 * */
	std::shared_ptr<int> addDoLoopMapping(int line_label, std::shared_ptr<int> line_mapping) {

		// Note that DO Loop entries are not final - once the exit line is seen, the value of exit_line_mapping will be modified.
		// 
		DO_LOOP_ENTRY x{
			line_label,
			line_mapping,
			// we need a temporary reference to a line mapping. We'll modify the *content* of this pointer later, while allowing it to still be managed by LineMapping.
			// This way, we can generate the correct offset without knowing the value required.
			LineMapping::addTemporaryLineMapping(0)				// This mapping will be changed later - this is the exit line mapping.
		};


		Logging::logInfoMessage("Adding DO loop mapping for " + std::to_string(line_label));
		Logging::logInfoMessage("Adding temporary line reference for loop end at " + std::to_string(line_label));
		// Add the DO loop mapping to the top of the queue
		do_mappings.push_back(x);
		return x.exit_line_mapping;
	}


	/**
	 * 
	 * 
	 * 	DO_LOOP_RETURN_VALUE retrieveDoLoopMapping(std::string line_label, int end_line_mapping)
	 * 	
	 * 	Inputs:
	 * 	 	line_label -> The line label of the statement to be checked. 
	 * 		int end_line_mapping -> The starting address of the statement to be checked.
	 * 
	 * 
	 * This function is is called on every newly processed statement in the program. The function checks a few things:
	 * a) There is a line label
	 * b) if that line label is referenced previously in a DO loop. 
	 * 
	 * 
	 * If the line has been previously referencede in a DO loop, several things happen. 
	 * 1) The entry to the do loop is retrospectively modified, modifying the three op code of an earlier instruction in order to point it at the correct address.
	 * We don't know where in memory the end of the DO loop is until we see it, so we can't exit the loop until we see the end. This code modifies earlier code to ensure that the 
	 * value we're exiting too is correct. 
	 * 2) This function then generates three op code to always jump back to the top of the loop. The do loop can ONLY exit from the top - jumping past this code.
	 **/
	DO_LOOP_RETURN_VALUE retrieveDoLoopMapping(std::string line_label, int end_line_mapping) {
		// This might contain multiple do loops
		// do_mappings is a FIFO - effectively. 
		std::vector<std::shared_ptr<ThreeOpCode> > do_loop_return_inject;
		if (do_mappings.empty()) {	
			// if empty - we're not in a do loop
			return { false, {} };
		}
		else {
			// This check runs on every line, so ignore the ones without line labels. 
			if (::stripWhitespaceString(line_label).empty()) {
				return { false, {} };
			}

			// Else - iterate through all possible DO loops. Note that we iterate BACKWARDS.
			// Once we've found a loop, we can inject code to jump back to the top of it.
			// Iterating backwards is important - this is what allows us to handle nested loops.
			for (std::vector<DO_LOOP_ENTRY>::reverse_iterator it = do_mappings.rbegin(); it != do_mappings.rend(); ++it) {

				// A temporary reference is required in order to maintain the correct offset.
				if ((*it).line_label == std::stoi(line_label)) {
					int new_val = *it->exit_line_mapping + end_line_mapping + do_loop_return_inject.size() + 2;

					ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
					Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");

					// This pointer is still controller by Line Mapping, we modify the value behind it.
					// This means that at a later point, Line Mapping will still offset this value, giving us the correct point. 
					// This technique means that a statement x lines before the final statement can be aware of what's coming.
					*it->exit_line_mapping = new_val;		// Modify the VALUE of the pre-existing line mapping.


					// Jump back to the start of the loop
					do_loop_return_inject.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
                    do_loop_return_inject.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode((*it).return_line_mapping, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_POSTITIVE, false)));
				}
			}
			return { true,  do_loop_return_inject };
		}
	}
};
