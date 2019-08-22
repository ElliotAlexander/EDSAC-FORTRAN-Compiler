#include "StandardLibrary/A94.h"

A94::A94(){
    A94::subroutine_text = "[A94]\nGKA3FT151@A0FT154@A1FT155@T152@H154@C169@T159@A154@R512FT158@H158@C170@T158@A158@A159@S166@G24@T152@A159@A168@T159@T152@T157@A154@E31@T152@A166@T157@T152@T152@H155@C169@T162@A155@R512FT161@H161@C170@T161@A161@A162@S166@G50@T152@A162@A168@T162@T152@T160@A155@E57@T152@A166@T160@T152@A159@S166@E66@T152@T163@T164@T165@E136@T152@A162@S166@E75@T152@T163@T164@T165@E136@T152@T152@A162@LDT162@A161@S166@T161@T152@A158@S161@A171@T164@T152@A159@T0DA162@T4D"
                           "A93@G[D6]FA0DR8FT165@T152@A157@S160@E104@T152@A166@T163@T152@A165@S167@S166@G117@T152@A165@RDT165@A164@A166@T164@T152@T152@S165@E133@T152@A165@S168@E135@T152@A165@LDT165@A164@S166@T164@E121@T152@T164@T152@T152@H165@C169@T156@A164@L512FA156@T156@A163@L64FL64FA156@T156@A156@T0FEFPFPFPFPFPFPDPDP1DPFP1FP128FPDPFP2047DPDP2047DP1024FP1023DP15DP7D..PZ";
    A94::is_enabled = false;
    A94::instruction_length = 172;
    A94::calling_value = std::shared_ptr<int>(new int(0));
    A94::name = "A94";
    A94::type = LIBRARY_TYPE::CLOSED_LIBRARY;
}


std::string A94::getRawRoutine() {
    return A94::subroutine_text;
}

bool A94::getEnabled(){
    return A94::is_enabled;
}

int A94::getLength(){
    return A94::instruction_length;
}

std::string A94::getName(){
    return A94::name;
}

void A94::setEnabled() {
    Libs::enableRoutine("D6");
    A94::is_enabled = true;
}

std::shared_ptr<int> A94::getCallingValue(){
    return A94::calling_value;
}


bool A94::applyOffset(int offset) {
    int new_val = *calling_value + offset;
    *calling_value = new_val;
    return true;
}

LIBRARY_TYPE A94::getType(){
    return A94::type;
}

std::string A94::getRoutineWithOutwardLibraryCalls(std::map<std::string, int> enabled_libraries) {
    const std::regex pattern_d6("\\[D6\\]");
    std::string address_d6 = std::to_string(enabled_libraries["D6"]);
    Logging::logInfoMessage("[A94]  Calling D6 at " + address_d6);
    std::string routine_with_d6 = std::regex_replace(subroutine_text, pattern_d6, address_d6);
    return routine_with_d6;
}
