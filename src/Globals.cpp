#include "Globals.h"

namespace Globals {

    std::vector<std::string> file_list;
    std::string output_file;
    bool output_file_set = false;
    bool allow_all_types = false;
    bool disable_line_length_warnings = false;
    bool dump_data_structures = false;
    bool dump_tokens = false;
    bool lazy_tokens =  false;
    bool dump_parsed_values = false;
    bool output_symbol_table_operations = false;
    bool dump_three_op_code = false;
    bool dump_symbol_table = false;
    bool output_function_mappings = false;
    bool output_regex_matching_strings = false;
    int base_memory_offset = 32;
	std::string BUFFER_FLUSH_NAME = "BUFFER_FLUSH";
}