#include "main.h"

#pragma warning(4:4233)

/**
 *  Entry point for the program. Handles the majority of control flow throughout the program, as well as acting as the backbone of the overarching program flow.
 *  Main explicitly handles building a list of input files, associated objects and associated ThreeOpCode. 
 *  Command Arguments are handled through CommandArgs.cpp.
 **/

int main(int argc, char* argv[]){
    
    
    clock_t tStart = clock();
    ::print_header();

    //
    // Initialise Helper classes
    //

    CommandArgs c(argc, argv); // Command args sets Global options inside Globals.cpp, and has no methods or return values.
    FileVerification fv;       // Used to process input files, validate their structure, accessibility, validity, etc.

    //
    // Initialise data structures
    //

    std::vector<FileContainer> input_files;                         // Generated list of VERIFIED file inputs. 
    std::vector<std::shared_ptr<ThreeOpCode> > program_body_toc = {};    // The generated three op code for instruction values. This does not include Data values.
    std::vector<std::shared_ptr<ThreeOpCode> > symbol_table_toc;    // Generated three op code for data values.
    std::vector<std::shared_ptr<ThreeOpCode>> toc_final_out;        // toc_final_out is the appended version of the final output, containing both program_body_toc, symbol_table_toc and generated library output.
    std::vector<std::string> edsac_out;                             // edsac_out is the final string representation of the outputted EDSAC instructions.
    std::vector<Segment> segment_list;                              // a list of all segments pulled in from files.


    Logging::logMessage("\n\n:: Loading File Inputs :: \n\n");

    for(int i = 0; i < Globals::file_list.size(); i++){                                     // Globals::file_list is generated from Command Line arguments inside CommandArgs.cpp.
        Logging::logMessage(" --- " + Globals::file_list[i] + " --- ");                     // Output a header for each file
        if(fv.verify(Globals::file_list[i])){                                               // FileVerification - ensure file is valid FORTRAN, properly formatted, accessible, etc. 
                                                                                            // File verificartion returns a bool depending on the validity of the input file.
            input_files.push_back(FileContainer(Globals::file_list[i]));                    // input_files_represents a verified list of FileContainers.
        } else {                                                                            // If the file verification fails...
            return PROGRAM_ERROR_EXIT_VALUE;                                                // In case of invalid file - Note that error messages are handled inside FileVerification.
        }
    }

    Logging::logConditionalMessage(Globals::dump_parsed_values, "\n:: Beginning preliminary parsing of files ::\n");    // Globals::dump_parsed_values is set in CommandArguments.

    for(std::vector<FileContainer>::size_type i = 0; i != input_files.size(); i++){     // Mutate files on at a time - files are ingested in alphabetical order.
        input_files[i].expandContinuations();                                           // Expand continuations into a singe statement. Continuations are treated as a single line, with the lines they previously occupied being replaced by comments.
                                                                                        // This allows a reference to the line number to be maintained.
        Logging::logConditionalMessage(Globals::dump_data_structures, std::string("\nSegment breakdown for " + Globals::file_list[i] + "\n"));
        Logging::logConditionalMessage(Globals::dump_tokens, "\n\n:: Beginning Tokenization :: \n");    

        std::vector<Segment> temp_segs = input_files[i].dissectSegments();   
        segment_list.insert(segment_list.begin(), temp_segs.begin(), temp_segs.end());
    }    // Dissect FileCOntainer object into 'segments' - a breakdown of programm structure into Main Program, Functions and Subroutines.
        

    // Note that this is completely C++14 dependent 
    std::sort(segment_list.begin(), segment_list.end(),     // Sort all segments so that program goes last.
            [] (const Segment& arg1, const Segment& arg2) { // Sort the list so that functions are considered > programs, hence programs go first.
                return arg2.getSegmentType() == SEGMENT_TYPE::PROGRAM ? true : false;    
            });

    for(int segment_index = 0; segment_index < segment_list.size(); segment_index++){           // Iterate through each segment of the program.
    
        Logging::logConditionalMessage(Globals::dump_tokens, " --- New Segment type=(" + getEnumString(segment_list.at(segment_index).getSegmentType()) + ") ---\n" );
        std::vector<Statement*> stmts = segment_list.at(segment_index).buildStatements();           // Break each segment of the program down into a series of 'Statement' objects.

        if(segment_list.at(segment_index).getSegmentType() == SEGMENT_TYPE::PROGRAM){
            program_body_toc.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("", THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_NEGATIVE, std::string("KZF"))));
        }

        for(int statement_index = 0; statement_index < stmts.size(); statement_index++){    // Iterate through each statement, from first to last. stmts represents a FILO queue. 
            Statement* s = stmts.at(statement_index);                                       // Acquire a pointer to each statement, for code clarity. This is not required, but greatly improves the readability of the following code.
            LineMapping::addLineMapping(s->getStatementLabel(), program_body_toc.size() - PROGRAM_LINE_MAPPING_RAW_OFFSET);        // Offset all line mappings by 1 - program_body.size() does not relate to the index. Subtract 1 to get the index.
            IDENTIFY_STATEMENT_RESULT_T identify_result = s->identifyStatement();           // Identify the type of statement - IDENTIFY_STATEMENT_RESULT_T encloses the true result and a boolean return vlaue.
            if(identify_result.result){                                                     // If the statement is successfully identified - continue. Else output an error message.
                if(identify_result.token->initaliseToken(s->getStatementBody())){           // Initialise the token object. Each token object's constructor only contains the necessary values to verify whether the incoming statement is of that tokens type.
                                                                                            // initialiseToken(std::string input) takes the body of the statement, and loads it into it's internal representation. 
                    std::vector<std::shared_ptr<ThreeOpCode> > statement_three_op_code = identify_result.token->generatetoc(program_body_toc.size() - PROGRAM_LINE_MAPPING_RAW_OFFSET);       // Once an internal representation is generated, we can generate a standard ThreeOpCode object from that.
                    program_body_toc.insert(program_body_toc.end(), statement_three_op_code.begin(), statement_three_op_code.end());                                                          // Add this three OP code to the program body.
                    DoLoopMapping::DO_LOOP_RETURN_VALUE ret = DoLoopMapping::retrieveDoLoopMapping(s->getStatementLabel(), program_body_toc.size() - PROGRAM_LINE_MAPPING_RAW_OFFSET);        // Check that the statement is not at the end of a DO Loop.   
                    program_body_toc.insert(program_body_toc.end(), ret.values.begin(), ret.values.end());                                                                                    // Add the statement to the final program body three op code/
                } else {
                    Logging::logErrorMessage("Failed to initialise token.");
                }
            } else {
                Logging::logErrorMessage("Failed to identify token. ");
            }
        }
        Logging::logNewLine();          // For user output formatting.
    };

    Logging::logConditionalMessage(Globals::dump_tokens, "\n --- End Tokenization --- \n\n");
        


    
	Logging::logMessage("\n:: Standard Library Initialisations :: \n\n");
    Libs::enableCommandLineActivatedRoutines();                                         // initialise library rouitnes.
    LibraryReturnContainer libs = Libs::buildLibraries(Globals::base_memory_offset);    // Build library routines in preparation for insertion into program text.
    Logging::logInfoMessage("Total library size: " + std::to_string(libs.offset));      // Output library routines to the user.

    symbol_table_toc = SymbolTableController::outputSymbolTable();    // Build the symbol table into a vector of Three Op Code. Note that all addresses in the symbol table are references, and may be modified upto the end of compilation.
    std::vector<std::shared_ptr<ThreeOpCode> > symbol_table_end_toc =  { 
        std::shared_ptr<ThreeOpCode>(new ThreeOpCode("", THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_POSTITIVE, std::string(" "))),
        std::shared_ptr<ThreeOpCode>(new ThreeOpCode("", THREE_OP_CODE_OPERATIONS::STOP_PROGRAM, std::string(" "))),
        std::shared_ptr<ThreeOpCode>(new ThreeOpCode("", THREE_OP_CODE_OPERATIONS::DATA_SET, false))
    };   // Generate a three op code array of all the data values in the symbol table.
    symbol_table_toc.insert(symbol_table_toc.end(), symbol_table_end_toc.begin(), symbol_table_end_toc.end());  // All programs end with 'EZPF' - i.e. Return to program start and stop execution.

    int program_body_offset = Globals::base_memory_offset + libs.offset;                // Offset program body by the base memory address (entry point) and the size of libraries. Libraries are appended to the start of the program, soo their size remains important.
    LineMapping::offsetLineMapping(program_body_offset);                                 

    int symbol_table_offset = program_body_offset + program_body_toc.size() - 1;        // Offset symvbol table by the size of the program body offset + the size of the program body. 
    SymbolTableController::offsetST(symbol_table_offset);                               


    toc_final_out = program_body_toc;
    toc_final_out.insert(toc_final_out.end(), symbol_table_toc.begin(), symbol_table_toc.end());    // Build final Three Op Code 
    edsac_out = EDSAC::generateEDSAC(toc_final_out, libs.output);                                   // Translate three op code into EDSAC instructions.

    ::printTOCOutput(toc_final_out, program_body_offset);                                           // Dump Three Op COde output to command line.
    SymbolTableController::printSymbolTables();                                                     // Dump symbol tables to command line

    Logging::logMessage("\n\n:: File Outputs :: \n\n");
    FileOutput::dumpThreeOpCodeFile(toc_final_out);                                                 // Dump three op code to file 
    FileOutput::dumpEDASCFile(edsac_out);                                                           // Dump edsac instrucrtions to file.

    Logging::logMessage((boost::format("\n\nTime taken: %.2fs") % ((double)(clock() - tStart)/CLOCKS_PER_SEC)).str());          // Compilation time
    Logging::logOutputSummary();        // Summary of error, warning and info messages.
    ::print_footer();                   //
}

