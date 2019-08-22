#ifndef _LIBRARY_BUILDER__HEADER_INCLUDED_
#define _LIBRARY_BUILDER__HEADER_INCLUDED_

#include <string>
#include <map>
#include <vector>

#include "D6.h"
#include "P6.h"
#include "P14.h"
#include "M20.h"
#include "A99.h"
#include "A98.h"
#include "A97.h"
#include "A96.h"
#include "A95.h"
#include "A94.h"
#include "Logging.h"
#include "Library.h"
#include "Globals.h"


struct LibraryReturnContainer {
	std::vector<std::string> output;
	int offset;
};

namespace Libs {
        std::vector<Library*> createVector();
        Library* getLibrary(std::string name);
		void enableRoutine(std::string name);
		std::string getLibraryContent(std::string name);
		void enableCommandLineActivatedRoutines();
		LibraryReturnContainer buildLibraries(int offset);
		std::shared_ptr<int> getLibraryLineMapping(std::string name);
}



#endif