#include "StandardLibrary/A98.h"

A98::A98(){
    A98::subroutine_text = "[A98]\nGKA3FT121@A0FT124@A1FT125@T122@H124@C139@T129@A124@R512FT128@H128@C140@T128@A128@A129@S136@G24@T122@A129@A138@T129@T122@T127@A124@E31@T122@A136@T127@T122@T122@H125@C139@T132@A125@R512FT131@H131@C140@T131@A131@A132@S136@G50@T122@A132@A138@T132@T122@T130@A125@E57@T122@A136@T130@T122@A129@S136@E66@T122@T133@T134@T135@E106@T122@A132@S136@E75@T122@T133@T134@T135@E106@T122@T122@A128@A131@S141@T134@T122@H129@V132@L8FT135@T122@A127@S130@E92@T122@A136@T133@T122@A135@S137@S136@G105@T122@A135@RDT135@A134@A136@T134@T122@T122@H135@C139@T126@A134@L512FA126@T126@A133@L64FL64FA126@T126@A126@T0FEFPFPFPFPFPFPDPDP1DPFP1FP128FPDPFP2047DPDP2047DP1024FP1023DP15DP7D..PZ";
    A98::is_enabled = false;
    A98::instruction_length = 142;
    A98::calling_value = std::shared_ptr<int>(new int(0));
    A98::name = "A98";
    A98::type = LIBRARY_TYPE::CLOSED_LIBRARY;
}


std::string A98::getRawRoutine() {
    return A98::subroutine_text;
}

bool A98::getEnabled(){
    return A98::is_enabled;
}

int A98::getLength(){
    return A98::instruction_length;
}

std::string A98::getName(){
    return A98::name;
}

void A98::setEnabled() {
    A98::is_enabled = true;
}

std::shared_ptr<int> A98::getCallingValue(){
    return A98::calling_value;
}


bool A98::applyOffset(int offset) {
    int new_val = *calling_value + offset;
    *calling_value = new_val;
    return true;
}

LIBRARY_TYPE A98::getType(){
    return A98::type;
}