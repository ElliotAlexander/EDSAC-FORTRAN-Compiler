#ifndef __FILEVERIFICATION_H_INCLUDED
#define __FILEVERIFICATION_H_INCLUDED

#include <string>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <Constants.h>
#include "CommandArgs.h"
#include "Globals.h"

class FileVerification {
    public:
        bool verify(std::string str);
    private:
        bool verify_exists(std::string str);
        bool verify_accessible(std::string str);
        bool verify_extension(std::string str);
        bool verify_regular_file(std::string str);
};
#endif