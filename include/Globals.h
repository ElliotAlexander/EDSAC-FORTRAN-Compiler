#ifndef __GLOBALS_H_INCLUDED
#define __GLOBALS_H_INCLUDED

#include <vector>
#include <string>

namespace Globals {
    extern std::vector<std::string> file_list;
    extern bool allow_all_types;
    extern bool disable_line_length_warnings;
    extern bool dump_data_structures;
    extern bool dump_tokens;
    extern bool lazy_tokens;
}

#endif