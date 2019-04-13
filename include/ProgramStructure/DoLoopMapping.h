#ifndef __DO_LOOP_MAPPING_
#define __DO_LOOP_MAPPING_

#include "Logging.h"
#include "Utils.h"

#include <vector>
#include <string>
#include <memory>

namespace DoLoopMapping {

	struct DO_LOOP_ENTRY {
		int line_label;
		std::shared_ptr<int> return_line_mapping;
	};

	struct DO_LOOP_RETURN_VALUE {
		bool result;
		std::shared_ptr<int> value;
	};


	bool addDoLoopMapping(int line_label, std::shared_ptr<int> line_mapping);
	DO_LOOP_RETURN_VALUE retrieveDoLoopMapping(std::string line_label);


	extern std::vector <DO_LOOP_ENTRY> do_mappings;


};



#endif