#include "StandardLibrary/LibraryBuilder.h"


namespace Libs {
    std::vector<Library*> libraries = createVector();

    std::vector<Library*> createVector() {
        std::vector<Library*> vec;

        vec.push_back(new D6());
        vec.push_back(new P6());
        vec.push_back(new P14());
        vec.push_back(new M20());
        vec.push_back(new A99());
        vec.push_back(new A98());
        vec.push_back(new A97());
        vec.push_back(new A96());
        vec.push_back(new A95());
        vec.push_back(new A94());
		return vec;
	}

    Library* getLibrary(std::string name) {
        for (Library* lib: libraries) {
            if (lib->getName() == name) {
                return lib;
            }
        }
        return nullptr;
    }

	std::shared_ptr<int> getLibraryLineMapping(std::string name){
		Library* lib = getLibrary(name);
		if (lib) {
		    return lib->getCallingValue();
		} else {
            Logging::logWarnMessage("Failed to find library " + name + " when accessing calling value. Is the library initialised?");
            return {};
		}
	}

	void enableRoutine(std::string name){
        Library* lib = getLibrary(name);
        if (lib) {
            if (!lib->getEnabled()) {
                lib->setEnabled();
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
        Library* lib = getLibrary(name);
        if (lib) {
            if (!lib->getEnabled()) {
                Logging::logInfoMessage("Library " + name + " is disabled!");
            }
        } else {
            Logging::logWarnMessage("Failed to find library " + name);
            return "";
        }
		return "";
	}


	LibraryReturnContainer buildLibraries(int offset) {
		Logging::logInfoMessage("Building bundled libraries.");
		int output_offset = 0;
        std::map<std::string, int> enabled_library_offsets;
        std::vector<std::string> output_string;

		for(auto & library_mapping : libraries){
			if(library_mapping->getEnabled() && library_mapping->getType() == LIBRARY_TYPE::CLOSED_LIBRARY){
			    int library_offset = offset + output_offset;
                library_mapping->applyOffset(library_offset);
				Logging::logInfoMessage("Adding subroutine " + library_mapping->getName() + "[" + std::to_string(library_mapping->getLength()) + "] at " + std::to_string(library_offset) + ". ");

				output_string.push_back(library_mapping->getRoutineWithOutwardLibraryCalls(enabled_library_offsets));

                enabled_library_offsets.insert(std::map<std::string, int>::value_type(library_mapping->getName(), library_offset));
                output_offset += library_mapping->getLength();
            } else {
				Logging::logInfoMessage("Skipping " + library_mapping->getName() + ", remains disabled");
			}
		}

		return {output_string, output_offset};
	}
}
