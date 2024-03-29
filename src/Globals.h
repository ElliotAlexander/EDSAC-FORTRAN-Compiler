#ifndef __GLOBALS_H_INCLUDED
#define __GLOBALS_H_INCLUDED

#include <vector>
#include <string>
#include <memory>

namespace Globals {

    extern std::vector<std::string> file_list;
    extern std::vector<std::string> library_list;
    extern std::string output_file;
    extern bool output_file_set;
    extern bool allow_all_types;
    extern bool output_line_mappings;
    extern bool dump_data_structures;
    extern bool dump_tokens;
    extern bool lazy_tokens;
    extern bool dump_parsed_values;
    extern bool output_symbol_table_operations;
    extern bool dump_three_op_code;
    extern bool dump_symbol_table;
    extern bool output_function_mappings;
	extern bool output_regex_matching_strings;
    extern int base_memory_offset;
	extern std::string BUFFER_FLUSH_NAME;
}


namespace OutputFlags {
    extern bool use_p6;
}

#endif