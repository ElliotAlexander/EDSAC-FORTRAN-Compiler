#ifndef __UTILS_H_INCLUDED
#define __UTILS_H_INCLUDED

#include <string>
#include <iostream>
#include "Constants.h"
#include "Logging.h"
#include <algorithm>
#include "ThreeOpCode/ThreeOpCode.h"
#include <vector>

bool lineIsComment(std::string line);
std::string getEnumString(int i);
std::string stripWhitespaceString(std::string input);
void printTOCOutput(std::vector<std::shared_ptr<ThreeOpCode>> three_op_code_arr, int total_offset);
bool printErrorLocation(int location, std::string);
void print_header();
void print_footer();


#endif