#include "StandardLibrary/A95.h"

A95::A95(){
    A95::subroutine_text = "[A95]\nGKA3FT60@A0FT62@T61@H62@C71@T65@A62@R512FT64@H64@C72@T64@A64@A65@S68@G22@T61@A65@A70@T65@T61@T63@A62@E29@T61@A68@T63@T61@T61@A65@T66@A74@A73@S64@T67@A67@S68@U67@G46@T61@A66@RDT66@E37@T61@A67@A68@U67@E56@T61@A66@LDT66@E46@T61@T61@A66@T0FEFPFPFPDPDPDPDPDPDP2047DP1024FP1023DP15DP7DP5D..PZ";
    A95::is_enabled = false;
    A95::instruction_length = 75;
    A95::calling_value = std::shared_ptr<int>(new int(0));
    A95::name = "A95";
    A95::type = LIBRARY_TYPE::CLOSED_LIBRARY;
}


std::string A95::getRawRoutine() {
    return A95::subroutine_text;
}

bool A95::getEnabled(){
    return A95::is_enabled;
}

int A95::getLength(){
    return A95::instruction_length;
}

std::string A95::getName(){
    return A95::name;
}

void A95::setEnabled() {
    A95::is_enabled = true;
}

std::shared_ptr<int> A95::getCallingValue(){
    return A95::calling_value;
}


bool A95::applyOffset(int offset) {
    int new_val = *calling_value + offset;
    *calling_value = new_val;
    return true;
}

LIBRARY_TYPE A95::getType(){
    return A95::type;
}
