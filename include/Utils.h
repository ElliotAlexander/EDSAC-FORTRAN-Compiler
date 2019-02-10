#ifndef __UTILS_H_INCLUDED
#define __UTILS_H_INCLUDED

#include <string>
#include <iostream>

#include "Constants.h"

bool lineIsComment(std::string line);
std::string getEnumString(int i);
std::string stripWhitespaceString(std::string input);
bool printErrorLocation(int location, std::string);

#endif