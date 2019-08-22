#include "StandardLibrary/D6.h"

D6::D6(){
    D6::subroutine_text = "[D6]\n"
                          "GKA3FT34@S4DE13@T4DSDTDE2@T4DAD"
                          "LDTDA4DLDE8@RDU4DLDA35@T6D"
                          "E25@U8DN8DA6DT6DH6DS6DN4DA4DYF"
                          "G21@SDVDTDEFW1526D..PZ";
    D6::is_enabled = false;
    D6::instruction_length = 36;
    D6::calling_value = std::shared_ptr<int>(new int(0));
    D6::name = "D6";
    D6::type = LIBRARY_TYPE::CLOSED_LIBRARY;
}


std::string D6::getRawRoutine() {
    return D6::subroutine_text;
}

bool D6::getEnabled(){
    return D6::is_enabled;
}

int D6::getLength(){
    return D6::instruction_length;
}

std::string D6::getName(){
    return D6::name;
}

void D6::setEnabled() {
    D6::is_enabled = true;
}

std::shared_ptr<int> D6::getCallingValue(){
    return D6::calling_value;
}


bool D6::applyOffset(int offset) {
    int new_val = *calling_value + offset;
    *calling_value = new_val;
    return true;
}

LIBRARY_TYPE D6::getType(){
    return D6::type;
}
