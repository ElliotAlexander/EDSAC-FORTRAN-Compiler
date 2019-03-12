#include "ThreeOpCode/ThreeOpCodeUtils.h"

std::string TOCOperationToString(int toc_op){
    switch (toc_op) {
        case  0:
            return std::string("ADD TO ACCUMULATOR");
        case 1:
            return std::string("SUBTRACT FROM ACCUMULATOR");
        case 2:
            return std::string("COPY TO MULTIPLIER");
        case 3:
            return std::string("MULTIPLY AND ADD TO ACCUMULATOR");
        case 4:
            return std::string("MULTIPLY AND SUBTRACT FROM ACCUMULATOR");
        case 5:
            return std::string("TRANSFER FROM ACCUMULATOR");
        case 6:
            return std::string("TRANSFER FROM ACCUMULATOR WITHOUT CLEARING");
        case 7:
            return std::string("COLLATE MULTIPLIER REGISTER");
        case 8:
            return std::string("SHIFT ACCUMULATOR RIGHT");
        case 9:
            return std::string("SHIFT ACCUMULATOR LEFT");
        case 10:
            return std::string("IF ACCUMULATOR POSITIVE");
        case 11:
            return std::string("IF ACCUMULATOR NEGATIVE");
        case 12:
            return std::string("READ NEXT SYMBOL");
        case 13:
            return std::string("PRINT SYMBOL");
        case 14:
            return std::string("READ NEXT SYMBOL");
        case 15:
            return std::string("NO OPERATION");
        case 16:
            return std::string("ROUND ACCUMULATOR TO 34 BITS");
        case 17:
            return std::string("STOP PROGRAM");
        case 18:
            return std::string("DATA SET");
        default:
            return std::string("UNIDENTIFIED INSTRUCTION");
    }
}