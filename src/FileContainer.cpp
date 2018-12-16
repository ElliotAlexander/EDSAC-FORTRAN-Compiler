#include "FileContainer.h"

FileContainer::FileContainer(std::string file_input){
    file_name = file_input;
    std::ifstream input(file_input);
    std::string line;

    int line_counter = 1;
    // Build full text string.
    while( std::getline( input, line ) ) {

        if(line == "" || !(line.find_first_not_of(' ') != std::string::npos)){
            continue;
        }

        // Add to vector
        file_text.push_back(line);

        // If line length warnings are enabled, warn the user on lines < 5 chars long.
        if((line.length() < 7) && !(Globals::disable_line_length_warnings) && !(::lineIsComment(line))) {
            std::cerr << StringConstants::WARN_TAG << "Line {'" << line << "'}[" << line_counter << "] has an unusually short length." << std::endl;
        }
        // Keep track.
        line_counter++;
    }

    // +filename[linecount]
    std::cout << "+" << file_name << "[" << file_text.size() << "]" << std::endl;    
    
    if(Globals::dump_data_structures){
        dumpFileText();
    }
}

bool FileContainer::expandContinuations(){
    int continuation_count = 1;
    
    // Iterate through lines
    for(std::vector<std::string>::size_type i = 0; i != file_text.size(); i++) {

        // Check line is not a comment.
        if(!::lineIsComment(file_text[i])){

            // Check we're not over the continuation limit.
            if(continuation_count == 20) {
                std::cerr << StringConstants::ERROR_TAG << "Over 20 Continuations detected! Aborting. Line[" << i-19 << "]{'" << file_text[i-continuation_count] << "'}." << std::endl;
                return false; 
            }
            
            // Check for a continuation
            // Ignore the first line.
            else if(
                    (file_text[i].at(5) != ' ') 
                    && (i != 0))
            {

                // Check if the first five characters are blank
                if(file_text[i].substr(0,4).find_first_not_of(' ') != std::string::npos){
                    std::cerr << StringConstants::ERROR_TAG << "Line {'" << file_text[i] << "'}[" << i + 1 << "] is marked as a continuation, but contains a label. Aborting." << std::endl;
                    return false;
                }

                // Get relevant section of current line (chars 6 -> onwards.)
                file_text[i].erase(0,5);
                    
                // Append current line to previous line.
                file_text[i-continuation_count] += file_text[i];

                // Mark current line as a comment.
                file_text[i] = std::string("C");

                // Iterate continuations.
                continuation_count += 1;
            
            } else {
                continuation_count = 1;
            }
        }
    }
    return true;
}

std::vector<Segment> FileContainer::dissectSegments(){
    
    bool in_segment_block = false; 
    SEGMENT_TYPE current_type; 
    int start_line = 0;
    for(std::vector<std::string>::size_type i = 0; i != file_text.size(); i++) {
        // Check line is not a comment.
        if(!::lineIsComment(file_text[i])){
            std::string useful_statement = file_text[i].substr(6, file_text[i].length());
            //std::cout << "Useful Statement = " << useful_statement << std::endl;
            //std::cout << "Useful Statment for a PROGRAM = " << useful_statement.substr(0,7) << std::endl;
            //std::cout << "Useful Statment for a SUBROUTINE = " << useful_statement.substr(0,10) << std::endl;
            if(useful_statement.substr(0,7) == "PROGRAM"){
                if(!in_segment_block) {
                    current_type = SEGMENT_TYPE::PROGRAM;
                    in_segment_block = true;
                    start_line = i;
                } else {
                    std::cerr << StringConstants::WARN_TAG << "PROGRAM Block detected inside another segment block [type=" << current_type << ",start=" << start_line+1 << ", end="<< i+1 << "]." << std::endl;
                }
            } else if(useful_statement.substr(0,3) == "END"){
                if(in_segment_block){
                    std::cout << "+" << ::getEnumString(current_type) << " [" << start_line + 1 << "," << i + 1 << "]."<< std::endl;

                    // Create Sub Vector
                    // Slow
                    auto first = file_text.cbegin() + start_line;
                    auto last = file_text.cbegin() + i + 1;

                    std::vector<std::string> sub_vec(first, last);

                    segment_arr.push_back(Segment(current_type, start_line, i, sub_vec));
                    in_segment_block = false;
                    current_type = {};

                } else {
                    std::cerr << "END detected outside of Segment Block [start=" << start_line + 1 << ", end="<<i + 1<< "]." << std::endl;
                }
            } else if(useful_statement.substr(0, 10) == "SUBROUTINE"){
                if(!in_segment_block){
                    current_type = SEGMENT_TYPE::SUBROUTINE;
                    start_line = i;
                    in_segment_block = true;
                } else {
                    std::cerr << StringConstants::WARN_TAG << "SUBROUTINE Block detected inside another segment block [type=" << current_type << ",start=" << start_line+1 << ", end="<< i+1 << "]." << std::endl;
                }
            } else if(useful_statement.substr(0, 8) == "FUNCTION"){
                if(!in_segment_block){
                    current_type = SEGMENT_TYPE::FUNCTION;
                    start_line = i;
                    in_segment_block = true;
                } else {
                    std::cerr << StringConstants::WARN_TAG << "FUNCTION Block detected inside another segment block [type=" << current_type << ",start=" << start_line+1 << ", end="<< i+1 << "]." << std::endl;
                }
            } else {
                if(!in_segment_block){
                    std::cerr << StringConstants::WARN_TAG << "Line ["<<i+1<<"] is not contained within a Segment block." << std::endl;
                } else {
                    continue;
                }
            }
        }
    }

    if(in_segment_block){
        std::cerr << StringConstants::WARN_TAG << "Program Segmentation completed inside a segment block. Are you missing an END statement?" << std::endl;
    };

    return segment_arr;
}

void FileContainer::dumpFileText(){
    std::cout << "\n:: Begin File Dump :: (Name=" << file_name << ") ::\n\n";
    for (std::vector<std::string>::const_iterator i = file_text.begin(); i != file_text.end(); ++i)
        std::cout << *i << ' ' << std::endl;
    std::cout << ":: End File Dump :: \n" << std::endl;
}
