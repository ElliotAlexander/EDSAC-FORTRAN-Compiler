#include "CommandArgs.h"
CommandArgs::CommandArgs(int argc, char* argv[]){


    // Configure Options
    cxxopts::Options options("./executable", "FORTRAN II Compiler built for the EDSAC Machine.");
    options.add_options()
        ("f,file", "Input File name", cxxopts::value<std::vector<std::string>>(Globals::file_list))
        ("x,allextensions", "Allow all file extensions", cxxopts::value<bool>()->default_value("false"))
        ("l,linemappings", "Output line mappings once they are loaded.", cxxopts::value<bool>()->default_value("false"))
        ("d,dumpfiles","Dump file contents as they're loaded. This is useful for logging build operations.", cxxopts::value<bool>()->default_value("false"))
        ("t,tokens","Dump Tokens.", cxxopts::value<bool>()->default_value("false"))
        ("p,parsedvalues","Dump Parsed Values from Statements while generating Three Op Codes.", cxxopts::value<bool>()->default_value("false"))
        ("h,help","Print help page", cxxopts::value<bool>()->default_value("false"))
        ("s,stops","Dump Symbol Table operations during parsing.", cxxopts::value<bool>()->default_value("false"))
        ("y,stdump","Dump Symbol Table once Compilation has finished.", cxxopts::value<bool>()->default_value("false"))
        ("c,toc","Dump Three Op Code output once parsed.", cxxopts::value<bool>()->default_value("false"))
        ("m,functionmappings","Output function mappings as they are loaded.", cxxopts::value<bool>()->default_value("false"))
        ("r,regex","Output regex for token matching", cxxopts::value<bool>()->default_value("false"))
        ("b,baseoffset","Base memory offset for bootloader. This is 32 by default.", cxxopts::value<int>(), "N")
        ("i,initialorders","Specify 1 or 2 for initial orders.", cxxopts::value<int>(), "Z")
        ("o,output","EDSAC Output file", cxxopts::value<std::string>(Globals::output_file))
        ("z,lazytokens","Enforce Lazy Tokenization - assume the first matching token is valid.", cxxopts::value<bool>()->default_value("false"));
    auto result = options.parse(argc, argv);

    if(result["help"].as<bool>()){
        Logging::logMessage(options.help());
        exit(1);
    }

    Logging::logMessage("\n:: Loading Command Arguments ::\n\n");

    if(result.count("baseoffset")){
        Globals::base_memory_offset = result["baseoffset"].as<int>();
        Logging::logMessage("+base memory offset = " + std::to_string(Globals::base_memory_offset));
    }

    if(result.count("initialorders")){
        Logging::logInfoMessage("Loaded initial orders");
        int orders = result["initialorders"].as<int>();
        if(orders == 2){
            Logging::logMessage("+initial orders 2");
            Globals::use_initial_orders_2 = true;
        } else {
            Logging::logWarnMessage("Failed to load initial orders: value " + std::to_string(orders));
        }
    }

    // Handle Boolean Arguments.
    if(result["allextensions"].as<bool>()){
        Logging::logMessage("+all-extensions");
        Globals::allow_all_types = true;
    }

    if(result["parsedvalues"].as<bool>()){
        Logging::logMessage("+parsed-values");
        Globals::dump_parsed_values = true;
    }

        // Handle Boolean Arguments.
    if(result["lazytokens"].as<bool>()){
        Logging::logMessage("+lazy tokens");
        Globals::lazy_tokens = true;
    }

    if(result["linemappings"].as<bool>()){
        Logging::logMessage("+line mappings");
        Globals::output_line_mappings = true;
    }

    if(result["dumpfiles"].as<bool>()){
        Logging::logMessage("+dump data structures");
        Globals::dump_data_structures = true;
    }

    if(result["tokens"].as<bool>()){
        Logging::logMessage("+dump tokens");
        Globals::dump_tokens = true;
    }

    if(result["stops"].as<bool>()){
        Logging::logMessage("+dump Symbol Table operations");
        Globals::output_symbol_table_operations = true;
    }

    if(result["stdump"].as<bool>()){
        Logging::logMessage("+dump Symbol Table");
        Globals::dump_symbol_table = true;
    }

    if(result["toc"].as<bool>()){
        Logging::logMessage("+dump Three Op Code");
        Globals::dump_three_op_code = true;
    }

    if(result["functionmappings"].as<bool>()){
        Logging::logMessage("+output Function Mappings");
        Globals::output_function_mappings = true;
    }


    if(result["regex"].as<bool>()){
        Logging::logMessage("+output Regex matching strings");
        Globals::output_regex_matching_strings = true;
    }

    // Handle positional file arguments.
    options.parse_positional({"f,file"});
    options.parse_positional({"o,output"});

    for(int i =0; i < result.count("file"); i++){
        Logging::logMessage("+load: " + Globals::file_list[i]);
    }

    if(result.count("output")){
        Logging::logMessage("+output file " + Globals::output_file);
        Globals::output_file_set = true;
    }

    Logging::logNewLine();
}  