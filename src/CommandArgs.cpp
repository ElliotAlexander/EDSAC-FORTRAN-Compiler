#include "CommandArgs.h"
CommandArgs::CommandArgs(int argc, char* argv[]){


    // Configure Options
    cxxopts::Options options("./executable", "FORTRAN II Compiler built for the EDSAC Machine.");
    options.add_options()
        ("f,file", "Input File name", cxxopts::value<std::vector<std::string>>(Globals::file_list))
        ("x,allextensions", "Allow all file extension", cxxopts::value<bool>()->default_value("false"))
        ("l,linelengthwarnings", "Disable warnings on short line length", cxxopts::value<bool>()->default_value("false"))
        ("d,dump","Dump data structures at each stage of parsing.", cxxopts::value<bool>()->default_value("false"))
        ("t,tokens","Dump Tokens.", cxxopts::value<bool>()->default_value("false"))
        ("p,parsedvalues","Dump Parsed Values from Statements while generating Three Op Codes.", cxxopts::value<bool>()->default_value("false"))
        ("h,help","Print help page", cxxopts::value<bool>()->default_value("false"))
        ("z,lazytokens","Enforce Lazy Tokenization - assume the first matching token is valid.", cxxopts::value<bool>()->default_value("false"));
    auto result = options.parse(argc, argv);

    if(result["help"].as<bool>()){
        Logging::logMessage(options.help());
        exit(1);
    }

    Logging::logMessage("\n:: Loading Command Arguments ::\n\n");

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

    if(result["linelengthwarnings"].as<bool>()){
        Logging::logMessage("+disabled line length warnings");
        Globals::disable_line_length_warnings = true;
    }

    if(result["dump"].as<bool>()){
        Logging::logMessage("+dump data structures");
        Globals::dump_data_structures = true;
    }

    if(result["tokens"].as<bool>()){
        Logging::logMessage("+dump tokens");
        Globals::dump_tokens = true;
    }

    // Handle positional file arguments.
    options.parse_positional({"f,file"});
    for(int i =0; i < result.count("file"); i++){
        Logging::logMessage("+load: " + Globals::file_list[i]);
    }

    Logging::logNewLine();
}  