#include "StandardLibrary/LibraryBuilder.h"


namespace Libs {

	std::map<std::string, Library*> library_mappings = createMap();

	std::map<std::string, Library*> createMap() {
		std::map<std::string, Library*> map;

		// P6
		map.insert(std::map<std::string, Library*>::value_type("P6", new P6()));

		Logging::logInfoMessage("Initalised map.");
		return map;
	}

	std::shared_ptr<int> getLibraryLineMapping(std::string name){
		std::map<std::string, Library*>::iterator it = library_mappings.find(name);
		if(it != library_mappings.end()){
			return (*it).second->getCallingValue();
		} else {
			Logging::logWarnMessage("Failed to find library " + name + " when accessing calling value. Is the library initialised?");
			return {};
		}
	}

	void enableRoutine(std::string name){
		std::map<std::string, Library*>::iterator it = library_mappings.find(name);
		if(it != library_mappings.end()){
			(*it).second->setEnabled();
			Logging::logInfoMessage("Enabled library " + name);
		} else {
			Logging::logWarnMessage("Failed to find library " + name);
		}
	}


	LibraryReturnContainer buildLibraries(int offset) {
		Logging::logInfoMessage("Building bundled libraries.");

		std::vector<std::string> output_string;
		int output_offset = 0;

		std::map<std::string, Library*>::iterator it = library_mappings.begin();

		for(; it != library_mappings.end(); ++it){
			if((*it).second->getEnabled()){

				Logging::logInfoMessage("Offsetting " + (*it).second->getName() + " by " + std::to_string(offset));
				(*it).second->applyOffset(offset);

				Logging::logInfoMessage("Adding subroutine " + (*it).second->getName() + "[" + std::to_string((*it).second->getLength()) + "].");
				output_string.push_back((*it).second->getRoutine());
				output_offset += (*it).second->getLength();
			} else {
				Logging::logInfoMessage("Skipping " + (*it).second->getName() + ", remains disabled");
			}
		}

		return {output_string, output_offset};
	}
}
