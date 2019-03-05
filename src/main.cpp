#include "main.h"

int main(int argc, char* argv[]){
    clock_t tStart = clock();
    ::print_header();

    // parse command arguments.
    CommandArgs c(argc, argv);
    
    // +instantiate
    FileVerification fv;

    // Setup data structure
    std::vector<FileContainer> input_files;
    Logging::logMessage("\n\n:: Loading File Inputs :: \n\n");

    // Iterate input files, 
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

    Logging::logMessage("\n:: Beginning preliminary parsing of files ::\n\n");
    // Mutate files
    for(std::vector<FileContainer>::size_type i = 0; i != input_files.size(); i++){ 
        Logging::logMessage(" --- " + Globals::file_list[i] + " ---\n");

        // Prepare data structures.
        input_files[i].expandContinuations();

        Logging::logMessage("\nFile Segment breakdown: \n");
        // Break files down into Segments.
        std::vector<Segment> segs = input_files[i].dissectSegments();

        // Validate + tokenize each segments
        Logging::logConditionalMessage(Globals::dump_tokens, "\nBeginning Tokenization: \n");
        for(int i = 0; i < segs.size(); i++){
            std::vector<Statement> stmts = segs.at(i).buildStatements();
            for(int x = 0; x < stmts.size(); x++){
                Statement* s = &stmts.at(x);
                IDENTIFY_STATEMENT_RESULT_T identify_result = s->identifyStatement();
                if(identify_result.result){
                    bool res = identify_result.token->initaliseToken(s->getStatementBody());
                } else {
                    Logging::logErrorMessage("Failed to identify token. ");
                }
            }
            Logging::logNewLine();
        };
        Logging::logMessage("\n --- End --- \n\n\n");
    }
    
    // TODO printf is bad
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    Logging::logOutputSummary();
    ::print_footer();
}


