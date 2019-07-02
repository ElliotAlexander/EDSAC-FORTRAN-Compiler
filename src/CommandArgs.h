#ifndef __ARGS_H_INCLUDED
#define __ARGS_H_INCLUDED

#include <cxxopts.hpp>
#include "Globals.h"
#include "Logging.h"


#define INITIAL_ORDERS_2 2

class CommandArgs {
    public:
        CommandArgs(int argc, char* argv[]);
    private:
};

#endif