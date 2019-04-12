#include "StandardLibrary/M20.h"


M20::M20(){
	M20::subroutine_text  = "[M20]\nPZZKM2037FGKP10KPZT43KP@\nZKM2037FGKP10KPZT43KP#0@\nZKM2037FGKP10KPZT45KP#0@I43KB2FQEF";
	M20::is_enabled = false;
	M20::instruction_length = 32;
	M20::calling_value = std::shared_ptr<int>(new int(0));
	M20::name = "M20";
	Logging::logInfoMessage("Initialised M20 library.");
}


std::string M20::getRoutine() {
	return M20::subroutine_text;
}

bool M20::getEnabled(){
	return M20::is_enabled;
}

int M20::getLength(){
	return M20::instruction_length;
}

std::string M20::getName(){
	return M20::name;
}

void M20::setEnabled() {
	M20::is_enabled = true;
}

std::shared_ptr<int> M20::getCallingValue(){
	return M20::calling_value;
}


bool M20::applyOffset(int offset) {
	int new_val = *calling_value + offset;
	*calling_value = new_val;
	return true;
}