#ifndef EDSAC_A94_H
#define EDSAC_A94_H

#include <string>
#include "Library.h"
#include "LibraryBuilder.h"
#include "Logging.h"

/**
 * A94: EDSAC Subroutine for 17-bit floating-point division
 */
class A94 : public Library {
public:
    A94();
    bool getEnabled();
    std::string getRawRoutine();
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
    std::string getRoutineWithOutwardLibraryCalls(std::map<std::string, int> enabled_libraries) override;
};

#endif //EDSAC_A94_H
