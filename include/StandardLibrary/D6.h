#ifndef EDSAC_D6_H
#define EDSAC_D6_H

#include <string>
#include "Library.h"
#include "LibraryBuilder.h"
#include "Logging.h"

/**
 * D6: EDSAC Subroutine for division
 */
class D6 : public Library {
public:
    D6();
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

#endif //EDSAC_D6_H
