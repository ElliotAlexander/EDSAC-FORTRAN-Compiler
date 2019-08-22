#include "StandardLibrary/A97.h"

A97::A97(){
    A97::subroutine_text = "[A97]\nGKA3FT66@A0FT71@A76@T70@T69@T67@A71@E15@T67@S71@T71@A72@T69@T67@A71@S72@E22@T67@T68@E63@T67@T67@A71@S73@S72@G36@T67@A71@RDT71@A70@A72@T70@E23@T67@T67@A71@S74@E49@T67@A71@LDT71@A70@S72@T70@E37@T67@T67@H71@C75@T68@A70@L512FA68@T68@A69@L64FL64FA68@T68@T67@A68@T0FEFPFPFPDPFP2047DPDP2047DP1024FP1023DP13F..PZ";
    A97::is_enabled = false;
    A97::instruction_length = 77;
    A97::calling_value = std::shared_ptr<int>(new int(0));
    A97::name = "A97";
    A97::type = LIBRARY_TYPE::CLOSED_LIBRARY;
}


std::string A97::getRawRoutine() {
    return A97::subroutine_text;
}

bool A97::getEnabled(){
    return A97::is_enabled;
}

int A97::getLength(){
    return A97::instruction_length;
}

std::string A97::getName(){
    return A97::name;
}

void A97::setEnabled() {
    A97::is_enabled = true;
}

std::shared_ptr<int> A97::getCallingValue(){
    return A97::calling_value;
}


bool A97::applyOffset(int offset) {
    int new_val = *calling_value + offset;
    *calling_value = new_val;
    return true;
}

LIBRARY_TYPE A97::getType(){
    return A97::type;
}