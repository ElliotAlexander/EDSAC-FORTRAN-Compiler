#include "main.h"

void print_header();
void print_footer();

int main(int argc, char* argv[]){
    print_header();

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
            return -1;
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << ":: Beginning preliminary parsing of files ::" << "\n\n";

    // Mutate files
    for(std::vector<FileContainer>::size_type i = 0; i != input_files.size(); i++){ 
        std::cout << " --- " << Globals::file_list[i] << " ---" << std::endl;
        input_files[i].expandContinuations();
        std::vector<Segment> segs = input_files[i].dissectSegments();
    }
    print_footer();
}

void print_header(){
    std::cout << "\n\n" << "===== " << "EDSAC FORTRAN II Compiler " << " =====" << "\n\n";
}

void print_footer(){
    std::cout << "\n\n" << "==== " << "End of runtime " << " ====" << "\n\n"; 
}