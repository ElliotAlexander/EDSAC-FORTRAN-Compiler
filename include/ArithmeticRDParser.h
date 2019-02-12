#ifndef __ARITHMETICRDPARSER_H_INCLUDED
#define __ARITHMETICRDPARSER_H_INCLUDED

#include <vector>
#include <string>
#include <cstdio>
#include <iostream>

#include "ArithmeticParser/Operation.h"
#include "ArithmeticParser/Value.h"
#include "ArithmeticParser/Variable.h"
#include "TOC.h"
#include "Constants.h"

TOC* parseADString(std::string input_string);

#endif