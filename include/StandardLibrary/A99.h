#ifndef EDSAC_A99_H
#define EDSAC_A99_H

#include <string>
#include "Library.h"
#include "LibraryBuilder.h"
#include "Logging.h"

/**
 * A99: EDSAC Subroutine for floating-point addition and subtraction
 */
class A99 : public Library {
public:
    A99();
    bool getEnabled();
    std::string getRoutine();
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

#endif //EDSAC_A99_H
