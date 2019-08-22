#ifndef EDSAC_A95_H
#define EDSAC_A95_H

#include <string>
#include "Library.h"
#include "LibraryBuilder.h"
#include "Logging.h"

/**
 * A95: EDSAC Subroutine for conversion from 17-bit floating-point number to integer
 */
class A95 : public Library {
public:
    A95();
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

};

#endif //EDSAC_A95_H
