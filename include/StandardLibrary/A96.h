#ifndef EDSAC_A96_H
#define EDSAC_A96_H

#include <string>
#include <regex>
#include "Library.h"
#include "LibraryBuilder.h"
#include "Logging.h"

/**
 * A96: EDSAC Subroutine for printing 17-bit floating-point number. Calls to P6 and P14.
 */
class A96 : public Library {
public:
    A96();
    bool getEnabled();
    std::string getRawRoutine();
    std::string getRoutineWithOutwardLibraryCalls(std::map<std::string, int> enabled_libraries) override;
    int getLength();
    std::string getName();
    void setEnabled();
    std::shared_ptr<int> getCallingValue();
    bool applyOffset(int offset);
    LIBRARY_TYPE getType();
private:
    int instruction_length;
    std::string subroutine_text;
    bool is_enabled;
    std::string name;
    std::shared_ptr<int> calling_value;
    LIBRARY_TYPE type;

};


#endif //EDSAC_A96_H
