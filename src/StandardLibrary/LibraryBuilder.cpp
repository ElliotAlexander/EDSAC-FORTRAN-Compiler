#include "StandardLibrary/LibraryBuilder.h"


namespace Libs {

	std::map<std::string, Library*> library_mappings = createMap();

	std::map<std::string, Library*> createMap() {
		std::map<std::string, Library*> map;

		// P6
		map.insert(std::map<std::string, Library*>::value_type("P6", new P6()));
        map.insert(std::map<std::string, Library*>::value_type("M20", new M20()));
        map.insert(std::map<std::string, Library*>::value_type("A99", new A99()));
        map.insert(std::map<std::string, Library*>::value_type("A98", new A98()));
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
			if(!(*it).second->getEnabled()){
				(*it).second->setEnabled();
				Logging::logInfoMessage("Enabled library " + name);
			}
		} else {
			Logging::logWarnMessage("Failed to find library " + name);
		}
	}

	void enableCommandLineActivatedRoutines(){
		for(std::vector<std::string>::iterator it = Globals::library_list.begin(); it != Globals::library_list.end(); ++it){
			enableRoutine((*it));
		}
	}

	std::string getLibraryContent(std::string name){
		std::map<std::string, Library*>::iterator it = library_mappings.find(name);
		if(it != library_mappings.end()){
			if(!(*it).second->getEnabled()){
				Logging::logInfoMessage("Library " + name + " is disabled!");
			} else {
				return (*it).second->getRoutine();
			}
		} else {
			Logging::logWarnMessage("Failed to find library " + name);
			return "";
		}
		return "";
	}


	LibraryReturnContainer buildLibraries(int offset) {
		Logging::logInfoMessage("Building bundled libraries.");

		std::vector<std::string> output_string;
		int output_offset = 0;

		for(auto & library_mapping : library_mappings){
			if(library_mapping.second->getEnabled() && library_mapping.second->getType() == LIBRARY_TYPE::CLOSED_LIBRARY){

				Logging::logInfoMessage("Offsetting " + library_mapping.second->getName() + " by " + std::to_string(offset + output_offset));
				library_mapping.second->applyOffset(offset + output_offset);

				Logging::logInfoMessage("Adding subroutine " + library_mapping.second->getName() + "[" + std::to_string(library_mapping.second->getLength()) + "].");
				output_string.push_back(library_mapping.second->getRoutine());
				output_offset += library_mapping.second->getLength();

            } else {
				Logging::logInfoMessage("Skipping " + library_mapping.second->getName() + ", remains disabled");
			}
		}

		return {output_string, output_offset};
	}
}
