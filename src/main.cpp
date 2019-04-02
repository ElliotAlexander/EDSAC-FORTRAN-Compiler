#include "main.h"

#pragma warning(4:4233)

int main(int argc, char* argv[]){
    clock_t tStart = clock();
    ::print_header();


    CommandArgs c(argc, argv);    
    FileVerification fv;
    std::vector<FileContainer> input_files;
    std::vector<std::shared_ptr<ThreeOpCode> > toc_program_body;


    Logging::logMessage("\n\n:: Loading File Inputs :: \n\n");
    for(int i = 0; i < Globals::file_list.size(); i++){
        Logging::logMessage(" --- " + Globals::file_list[i] + " --- ");
        // Verify their properties.
        if(fv.verify(Globals::file_list[i])){
            // Add to data structure.
            input_files.push_back(FileContainer(Globals::file_list[i]));
        } else {
            // Invalid file - error messages are handled within FileVerification.cpp
            return -1;
        }
    }

    Logging::logConditionalMessage(Globals::dump_parsed_values, "\n:: Beginning preliminary parsing of files ::\n");

    // Mutate files
    for(std::vector<FileContainer>::size_type i = 0; i != input_files.size(); i++){ 
        // Prepare data structures.
        input_files[i].expandContinuations();

        Logging::logConditionalMessage(Globals::dump_data_structures, std::string("\nSegment breakdown for " + Globals::file_list[i] + "\n"));
        // Break files down into Segments.
        std::vector<Segment> segs = input_files[i].dissectSegments();
        Logging::logConditionalMessage(Globals::dump_tokens, "\n\n:: Beginning Tokenization :: \n");
        // Iterate through each segment of the program.
        for(int segment_index = 0; segment_index < segs.size(); segment_index++){
            Logging::logConditionalMessage(Globals::dump_tokens, " --- New Segment type=(" + getEnumString(segs.at(segment_index).getSegmentType()) + ") ---\n" );

            // Break each segment down into a list of statements.
            std::vector<Statement*> stmts = segs.at(segment_index).buildStatements();
            // Iterate through each statement of the segment.
            for(int statement_index = 0; statement_index < stmts.size(); statement_index++){
                // Build a statement object
                Statement* s = stmts.at(statement_index);
                LineMapping::addLineMapping(s->getStatementLabel(), toc_program_body.size());
                // Identify (tokenize) the statement.
                IDENTIFY_STATEMENT_RESULT_T identify_result = s->identifyStatement();
                // If successfully identified.
                if(identify_result.result){
                    // Initialise the token object
                    if(identify_result.token->initaliseToken(s->getStatementBody())){
                        // generatae three op code object
                        std::vector<std::shared_ptr<ThreeOpCode> > statement_three_op_code = identify_result.token->generatetoc(toc_program_body.size());

                        // add to the program body
                        toc_program_body.insert(toc_program_body.end(), statement_three_op_code.begin(), statement_three_op_code.end());
                    } else {
                        Logging::logErrorMessage("Failed to initialise token.");
                    }
                } else {
                    Logging::logErrorMessage("Failed to identify token. ");
                }
            }
            Logging::logNewLine();
        };

        Logging::logConditionalMessage(Globals::dump_tokens, "\n --- End Tokenization --- \n\n");
    }        

    Libs::enableRoutine("P6");
    LibraryReturnContainer libs = Libs::buildLibraries(Globals::base_memory_offset);
    Logging::logInfoMessage("Total library size: " + std::to_string(libs.offset));


    NoRepeatedAccClear noaccclear;
    toc_program_body = noaccclear.processProgram(toc_program_body);

    // Add the symbol table to the start of memory
    std::vector<std::shared_ptr<ThreeOpCode> > symbol_table_toc = SymbolTableController::outputSymbolTable();

    // Offset line mappings by the size of the symbol table
    int program_body_offset = symbol_table_toc.size() + Globals::base_memory_offset + libs.offset;
    int symbol_table_offset = Globals::base_memory_offset + libs.offset;
    
    Logging::logInfoMessage("Offsetting Program Body output by " + std::to_string(program_body_offset));
    LineMapping::offsetLineMapping(program_body_offset);

    Logging::logInfoMessage("Offsetting Symbol Table by " + std::to_string(symbol_table_offset));
    SymbolTableController::offsetST(symbol_table_offset);

    std::vector<std::shared_ptr<ThreeOpCode>> toc_final_out = symbol_table_toc;
    toc_final_out.insert(toc_final_out.end(), toc_program_body.begin(), toc_program_body.end());
    std::vector<std::string> edsac_out = EDSAC::generateEDSAC(toc_final_out, libs.output);

    // Command line output
    ::printTOCOutput(toc_final_out, program_body_offset);
    SymbolTableController::printSymbolTables();

    Logging::logMessage("\n\n:: File Outputs :: \n\n");
    FileOutput::dumpThreeOpCodeFile(toc_final_out);
    FileOutput::dumpEDASCFile(edsac_out);

    Logging::logMessage((boost::format("\n\nTime taken: %.2fs") % ((double)(clock() - tStart)/CLOCKS_PER_SEC)).str());
    Logging::logOutputSummary();
    ::print_footer();
}

