#include "StandardLibrary/A96.h"

A96::A96(){
    A96::subroutine_text = "[A96]\nGKA3FT103@"
                           "A0FT105@T104@H105@C117@T108@A105@R512FT107@H107@C118@T107@A107@A108@S113@G22@T104@A108@A115@T108@T104@T106@A105@E29@T104@A113@T106@T104@T104@A108@T109@A122@A121@S107@T110@A110@S113@U110@G46@T104@A109@RDT109@E37@T104@A110@A113@U110@E56@T104@A109@LDT109@E46@T104@T104@A108@T111@A123@A107@S121@T112@A112@S113@U112@G73@T104@A111@LDT111@E64@T104@A112@A113@U112@E83@T104@A111@RDT111@E73@T104@H111@C116@T111@A106@S113@G91@O119@T104@A109@T0F"
                           "A94@G[P6]FO120@T104@A111@T0D"
                           "A100@G[P14]FP1024FEFPFPFPDPDPDPDPDPDPDPDP2047DP1024F*2047DP1023DP15DAFMFP7DP5DP2D"
                           "..PZ";
    A96::is_enabled = false;
    A96::instruction_length = 124;
    A96::calling_value = std::shared_ptr<int>(new int(0));
    A96::name = "A96";
    A96::type = LIBRARY_TYPE::CLOSED_LIBRARY;
}


std::string A96::getRawRoutine() {
    return A96::subroutine_text;
}

bool A96::getEnabled(){
    return A96::is_enabled;
}

int A96::getLength(){
    return A96::instruction_length;
}

std::string A96::getName(){
    return A96::name;
}

void A96::setEnabled() {
    Libs::enableRoutine("P6");
    Libs::enableRoutine("P14");
    A96::is_enabled = true;
}

std::shared_ptr<int> A96::getCallingValue(){
    return A96::calling_value;
}


bool A96::applyOffset(int offset) {
    int new_val = *calling_value + offset;
    *calling_value = new_val;
    return true;
}

LIBRARY_TYPE A96::getType(){
    return A96::type;
}

std::string A96::getRoutineWithOutwardLibraryCalls(std::map<std::string, int> enabled_libraries) {
    const std::regex pattern_p6("\\[P6\\]");
    const std::regex pattern_p14("\\[P14\\]");
    std::string address_p6 = std::to_string(enabled_libraries["P6"]);
    std::string address_p14 = std::to_string(enabled_libraries["P14"]);
    Logging::logInfoMessage("[A96]  Calling P6 at " + address_p6);
    Logging::logInfoMessage("[A96]  Calling P14 at " + address_p14);
    std::string routine_with_p6 = std::regex_replace(subroutine_text, pattern_p6, address_p6);
    std::string routine_with_p6_and_p14 = std::regex_replace(routine_with_p6, pattern_p14, address_p14);
    return routine_with_p6_and_p14;
}
