#ifndef _LIBRARY_BUILDER__HEADER_INCLUDED_
#define _LIBRARY_BUILDER__HEADER_INCLUDED_

#include <string>
#include <map>

#include "P6.h"
#include "Logging.h"
#include "Library.h"
#include <vector>

struct LibraryReturnContainer {
	std::vector<std::string> output;
	int offset;
};

namespace Libs {

		extern std::map<std::string, std::shared_ptr<int> > library_line_mappings;
		extern std::map<std::string, Library*> library_mappings;

		std::map<std::string, Library*> createMap();
		void enableRoutine(std::string name);
		LibraryReturnContainer buildLibraries();

	
}



#endif