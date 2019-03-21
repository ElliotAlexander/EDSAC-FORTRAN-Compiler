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

        Logging::logMessage(std::string("\nSegment breakdown for " + Globals::file_list[i] + "\n"));
        // Break files down into Segments.
        std::vector<Segment> segs = input_files[i].dissectSegments();
        // Validate + tokenize each segments
        Logging::logConditionalMessage(Globals::dump_tokens, "\n:: Beginning Tokenization :: \n");
        // Iterate through each segment of the program.
        for(int segment_index = 0; segment_index < segs.size(); segment_index++){
            Logging::logMessage(" --- New Segment type=(" + getEnumString(segs.at(i).getSegmentType()) + ") ---\n" );

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
                    if(identify_result.token->initaliseToken(s->getStatementBody())){
                        std::vector<std::shared_ptr<ThreeOpCode> > statement_three_op_code = identify_result.token->generatetoc(toc_program_body.size());
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

        Logging::logMessage("\n --- End Tokenization --- \n\n");
        ::offsetST(toc_program_body.size());
        ::printTOCOutput(toc_program_body);
    }
        
        
    ::printSymbolTables();
    Logging::logMessage((boost::format("Time taken: %.2fs\n") % ((double)(clock() - tStart)/CLOCKS_PER_SEC)).str());
    Logging::logOutputSummary();
    ::print_footer();
}

