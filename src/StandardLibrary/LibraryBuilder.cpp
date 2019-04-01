#include "StandardLibrary/LibraryBuilder.h"


LibraryBuilder::LibraryBuilder() {
	library_mappings.insert(std::map<std::string, Library*>::value_type("P6", new P6()));
	Logging::logInfoMessage("initialised");
}


void LibraryBuilder::enableRoutine(std::string name){
	std::map<std::string, Library*>::iterator it = library_mappings.begin();
	for(; it != library_mappings.end(); ++it){
		if(it->second->getName() == name){
			it->second->setEnabled();
			Logging::logInfoMessage("Enabled library " + name);
			return;
		}
	}
}


LibraryReturnContainer LibraryBuilder::buildLibraries() {
	std::vector<std::string> output_string;
	int output_offset;
	std::map<std::string, Library*>::iterator it = library_mappings.begin();
	for(; it != library_mappings.end(); ++it){
		if((*it).second->getEnabled()){
			Logging::logInfoMessage("Adding subroutine " + (*it).second->getName() + "[" + std::to_string((*it).second->getLength()) + "].");
			output_string.push_back((*it).second->getRoutine());
			output_offset += (*it).second->getLength();
		}
	}

	return {output_string, output_offset};
}
