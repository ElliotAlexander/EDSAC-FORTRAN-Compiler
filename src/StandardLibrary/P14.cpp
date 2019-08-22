#include "StandardLibrary/P14.h"

P14::P14(){
    P14::subroutine_text = "[P14]\nGKT45KXF\n"
                           "O40K#FTZ"
                           "A45@U4@A22@T39@AFE8@O40@O41@T4@AD"
                           "E15@TDSDO@E16@O42@PHTDH44@A4@"
                           "T4@VDU1FO1FFFSFG29@S43@G30@O41@"
                           "A43@L4FTDA4@LDE20@O42@LDG20@EF"
                           "@F&F!FQFJFP2F"
                           "..PZ";
    P14::is_enabled = false;
    P14::instruction_length = 46;
    P14::calling_value = std::shared_ptr<int>(new int(0));
    P14::name = "P14";
    P14::type = LIBRARY_TYPE::CLOSED_LIBRARY;
}


std::string P14::getRawRoutine() {
    return P14::subroutine_text;
}

bool P14::getEnabled(){
    return P14::is_enabled;
}

int P14::getLength(){
    return P14::instruction_length;
}

std::string P14::getName(){
    return P14::name;
}

void P14::setEnabled() {
    P14::is_enabled = true;
}

std::shared_ptr<int> P14::getCallingValue(){
    return P14::calling_value;
}


bool P14::applyOffset(int offset) {
    int new_val = *calling_value + offset;
    *calling_value = new_val;
    return true;
}

LIBRARY_TYPE P14::getType(){
    return P14::type;
}