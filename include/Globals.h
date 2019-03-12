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
    extern bool dump_parsed_values;
    extern bool output_symbol_table_operations;
    extern bool dump_three_op_code;
    extern bool dump_symbol_table;
}

#endif