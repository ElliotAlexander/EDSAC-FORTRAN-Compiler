#include "StandardLibrary/P6.h"


P6::P6(){
	P6::subroutine_text  = "[P6]\nGKA3FT25@H29@VFT4DA3@TFH30@S6@T1FV4DU4DAFG26@TFTFO5FA4DF4FS4FL4FT4DA1FS3@G9@EFSFO31@E20@J995FJF!F..PZ";
	P6::is_enabled = false;
	P6::instruction_length = 32;
	P6::calling_value = std::shared_ptr<int>(new int(0));
	P6::name = "P6";
}


std::string P6::getRoutine() {
	return P6::subroutine_text;
}

bool P6::getEnabled(){
	return P6::is_enabled;
}

int P6::getLength(){
	return P6::instruction_length;
}

std::string P6::getName(){
	return P6::name;
}

void P6::setEnabled() {
	P6::is_enabled = true;
}

std::shared_ptr<int> P6::getCallingValue(){
	return P6::calling_value;
}


bool P6::applyOffset(int offset) {
	int new_val = *calling_value + offset;
	*calling_value = new_val;
	return true;
}