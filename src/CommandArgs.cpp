#include "CommandArgs.h"

// Command line options are processed by cxxopts.h
// cxxopts.h is a header only library
// This function processes command arguments, and sets a variety of global flags depending on their values.
// Inputs:
//      argc => number of command line arguments, from main.cpp
//      argv => Command Line argument input, from main.cpp
//

CommandArgs::CommandArgs(int argc, char* argv[]){


    cxxopts::Options options("./executable", "FORTRAN II Compiler built for the EDSAC Machine.");

    options.add_options()

        // String options

        ("f,file", "Input File name", cxxopts::value<std::vector<std::string>>(Globals::file_list))                                                             // Generate a list of input files
        ("e,library", "Add Standard Library", cxxopts::value<std::vector<std::string>>(Globals::library_list))                                                  // takes an input string of the name of a library.  i.e. -e P6
        ("o,output","EDSAC Output file", cxxopts::value<std::string>(Globals::output_file))                                                                     // the output .edsac file to be generated.

        // Boolean Options

        ("x,allextensions", "Allow all file extensions", cxxopts::value<bool>()->default_value("false"))                                                        // Disables warnings about unknown file extensions.
        ("l,linemappings", "Output line mappings once they are loaded.", cxxopts::value<bool>()->default_value("false"))                                        // Outputs a table of line mappings.
        ("d,dumpfiles","Dump file contents as they're loaded. This is useful for logging build operations.", cxxopts::value<bool>()->default_value("false"))    // Dump files to the commmand line as they are loaded.                
        ("t,tokens","Dump Tokens.", cxxopts::value<bool>()->default_value("false"))                                                                             // Dump tokens to the command line as they are loaded.
        ("p,parsedvalues","Dump Parsed Values from Statements while generating Three Op Codes.", cxxopts::value<bool>()->default_value("false"))                // Dump parsed token values to the command line as they are loaded.
        ("h,help","Print help page", cxxopts::value<bool>()->default_value("false"))                                                                            //
        ("s,stops","Dump Symbol Table operations during parsing.", cxxopts::value<bool>()->default_value("false"))                                              // Dump Operations on the symbol table during compilation.
        ("y,stdump","Dump Symbol Table once Compilation has finished.", cxxopts::value<bool>()->default_value("false"))                                         // Dump the symbol table to the command line once compilation has finished. 
        ("c,toc","Dump Three Op Code output once parsed.", cxxopts::value<bool>()->default_value("false"))                                                      // Dump three op code output once compilation has finished.
        ("m,functionmappings","Output function mappings as they are loaded.", cxxopts::value<bool>()->default_value("false"))                                   // Dump funciton mappings to the command line as they are loaded.
        ("r,regex","Output regex for token matching", cxxopts::value<bool>()->default_value("false"))                                                           // Output a full set of regex used for identifying tokens.
        ("z,lazytokens","Enforce Lazy Tokenization - assume the first matching token is valid.", cxxopts::value<bool>()->default_value("false"));               // Largely irrelevant - mostly used for debugging and development. once the compiler finds a valid token, it assumes its correctness with this flag enabled.
        
        // Integer options

        ("b,baseoffset","Base memory offset for bootloader. This is 32 by default.", cxxopts::value<int>(), "N")                                                // The base memory offset from which the program will start.
        ("i,initialorders","Specify 1 or 2 for initial orders.", cxxopts::value<int>(), "Z");                                                                   // Specify initial orders 1 or 2. 
    
    

    // Call cxxopts to parse the command line arguments.
    auto result = options.parse(argc, argv);
    if(result["help"].as<bool>()){
        Logging::logMessage(options.help());
        exit(1);
    }

    Logging::logMessage("\n:: Loading Command Arguments ::\n\n");

    //
    //
    //      The following statements set the global options for each argument, providing it is specified.
    //
    //

    if(result.count("baseoffset")){
        Globals::base_memory_offset = result["baseoffset"].as<int>();
        Logging::logMessage("+base memory offset = " + std::to_string(Globals::base_memory_offset));
    }


    // This option is essentiall deprecated, as initial orders 1 is not supported.
    // 
    if(result.count("initialorders")){
        int orders = result["initialorders"].as<int>();
        if(orders == INITIAL_ORDERS_2){
            Logging::logMessage("+initial orders 2");
            Globals::use_initial_orders_2 = true;
        } else {
            Logging::logWarnMessage("Failed to load initial orders: value " + std::to_string(orders));
        }
    }

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
    options.parse_positional({"e,library"});
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