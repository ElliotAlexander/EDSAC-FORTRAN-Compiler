#include "main.h"

void print_header();
void print_footer();

int main(int argc, char* argv[]){
    ::print_header();

    // parse command arguments.
    CommandArgs c(argc, argv);
    
    // +instantiate
    FileVerification fv;

    // Setup data structure
    std::vector<FileContainer> input_files;

    // Pretify
    std::cout << std::endl;

    std::cout << std::endl << ":: Loading File Inputs ::" << "\n\n";

    // Iterate input files, 
    for(int i = 0; i < Globals::file_list.size(); i++){

        std::cout << " --- " << Globals::file_list[i] << " ---" << std::endl;

        // Verify their properties.
        if(fv.verify(Globals::file_list[i])){
            // Add to data structure.
            input_files.push_back(FileContainer(Globals::file_list[i]));
        } else {
            // Invalid file - error messages are handled within FileVerification.cpp
            return -1;
        }

        // Prettify
        std::cout << std::endl;
    }

    std::cout << std::endl << ":: Beginning preliminary parsing of files ::" << "\n\n";

    // Mutate files
    for(std::vector<FileContainer>::size_type i = 0; i != input_files.size(); i++){ 

        std::cout << " --- " << Globals::file_list[i] << " ---\n";

        // Prepare data structures.
        input_files[i].expandContinuations();

        std::cout << "\nFile Segment breakdown: \n";
        // Break files down into Segments.
        std::vector<Segment> segs = input_files[i].dissectSegments();

        // Validate + tokenize each segments
        std::cout << "\nBeginning Tokenization: \n";
        for(int i = 0; i < segs.size(); i++){
            std::vector<Statement> stmts = segs.at(i).buildStatements();
        };
        std::cout << "\n --- End --- \n\n\n";
    }
    ::print_footer();
}