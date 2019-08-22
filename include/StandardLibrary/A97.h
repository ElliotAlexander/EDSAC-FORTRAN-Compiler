#ifndef EDSAC_A97_H
#define EDSAC_A97_H

#include <string>
#include "Library.h"
#include "LibraryBuilder.h"
#include "Logging.h"

/**
 * A97: EDSAC Subroutine for conversion from integer to 17-bit floating-point
 */
class A97 : public Library {
public:
    A97();
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



#endif //EDSAC_A97_H
