#ifndef __ARITHMETICRDPARSER_H_INCLUDED
#define __ARITHMETICRDPARSER_H_INCLUDED

#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "ArithmeticParser/Operation.h"
#include "ArithmeticParser/Value.h"
#include "ArithmeticParser/Variable.h"
#include "RDParseTreeNode.h"
#include <memory>
#include "Logging.h"

std::unique_ptr<RDParseTreeNode> parseADString(std::string input_string);

#endif