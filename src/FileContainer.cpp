#include "FileContainer.h"

FileContainer::FileContainer(std::string file_input){
    file_name = file_input;
    std::ifstream input(file_input);
    std::string line;

    int line_counter = 1;
    // Build full text string.
    while( std::getline( input, line ) ) {
        // We comment out lines that are too short to be actual statements. 
        line = removeShortLines(line, line_counter);
        line = removeNewlines(line);

        // Add to vector
        file_text.push_back(line);

        // Keep track.
        line_counter++;
    }

    Logging::logMessage("Loaded " + file_name + "[" + std::to_string(file_text.size()) + "] successfully. ");
    if(Globals::dump_data_structures){
        dumpFileText();
    }
}

void FileContainer::dumpFileText(){
    Logging::logMessage("Begin File Dump(Name=" + file_name + "):\n");
    for (std::vector<std::string>::const_iterator i = file_text.begin(); i != file_text.end(); ++i)
        Logging::logMessage(*i + ' ');
    Logging::logMessage("\nEnd File Dump\n");
}

bool FileContainer::expandContinuations(){
    int continuation_count = 1;
    
    // Iterate through lines
    for(std::vector<std::string>::size_type i = 0; i != file_text.size(); i++) {

        // Check line is not a comment.
        if(!::lineIsComment(file_text[i])){

            // Check we're not over the continuation limit.
            if(continuation_count == 20) {
                Logging::logErrorMessage("Over 20 Continuations detected! Aborting. Line[" + std::to_string(i-19) + "]{'" + file_text[i-continuation_count] + "'}.");
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
                    Logging::logErrorMessage("Line {'" + file_text[i] + "'}[" + std::to_string(i+1) + "] is marked as a continuation, but contains a label. Aborting.");
                    return false;
                }

                std::string line_text_backup = file_text[0];

                // Get relevant section of current line (chars 6 -> onwards.)
                file_text[i].erase(0,6);
                if(file_text[i].length() == 0){
                    Logging::logErrorMessage("Empty continuation - Continuation labelled lines must contained at least one character.");
                    ::printErrorLocation(7, line_text_backup);
                }
                    
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

std::string FileContainer::removeShortLines(std::string line, int line_counter){
        // If line length warnings are enabled, warn the user on lines < 5 chars long.
        if((line.length() < 7) && !(Globals::disable_line_length_warnings) && !(::lineIsComment(line))) {
            Logging::logWarnMessage("Line { " + line + " }[" + std::to_string(line_counter) + "] has an unusually short length. It will be marked as a comment and ignored.");
            line.insert(0, "C");
        }
        return line;
}

std::string FileContainer::removeNewlines(std::string line){
    std::string::size_type pos = 0; 

    // Some of these files have a single CR ending the line.
    while ( ( pos = line.find ("\r",pos) ) != std::string::npos )
    {
        line.erase ( pos, 2 );
    } 

    pos = 0;
    while ( ( pos = line.find ("\r\n",pos) ) != std::string::npos )
    {
        line.erase ( pos, 2 );
    } 
    return line;
}

std::vector<Segment> FileContainer::dissectSegments(){
    
    bool in_segment_block = false; 
    bool in_main_block = true;
    SEGMENT_TYPE current_type = {}; 
    int start_line = 0;

    for(std::vector<std::string>::size_type i = 0; i != file_text.size(); i++) {

        // Check line is not a comment.
        if(!::lineIsComment(file_text[i])){

            // Get line from file.
            std::string useful_statement = file_text[i].substr(6, file_text[i].length());

            if(useful_statement.substr(0,3) == "END"){
                if(in_segment_block){
                    Logging::logErrorMessage( "END statement found inside a segment block. Are you missing a return? [" + std::to_string(i) + "].");
                } else if(in_main_block){
                    in_main_block = false;
                    std::vector<std::string> segment_text;
                    for(int x = start_line; x < ( i+1 ); x++){
                        segment_text.push_back(file_text.at(x));
                    }
                    Logging::logMessage("+" + ::getEnumString(SEGMENT_TYPE::PROGRAM) + " [" + std::to_string(start_line + 1) + "," + std::to_string(i + 1) + "]");
                    Logging::logInfoMessage("Found end of Program [" + std::to_string(i + 1) + "].");
                    segment_arr.push_back(Segment(current_type, start_line, i, segment_text));
                } else {
                    Logging::logWarnMessage("END detected outside of Main Program Block[" + std::to_string(i) + "]");
                }
            } else if(useful_statement.substr(0, 6) == "RETURN") {
                if(in_segment_block){
                    std::vector<std::string> segment_text;
                    for(int x = start_line; x < ( i+1 ); x++){
                        segment_text.push_back(file_text.at(x));
                    }

                    Logging::logInfoMessage("+" + ::getEnumString(current_type) + " [" + std::to_string(start_line + 1) + "," + std::to_string(i + 1) + "]{" + ::stripWhitespaceString(segment_text.at(0)) + "}.");
                    segment_arr.push_back(Segment(current_type, start_line, i, segment_text));
                    in_segment_block = false;
                    start_line = i+1;
                    current_type = {};
                } else {
                    Logging::logWarnMessage("RETURN detected outside of Subroutine Block [start=" + std::to_string(start_line + 1) +  ", end=" + std::to_string(i+1) +  "].");
                }
            } else if(useful_statement.substr(0, 10) == "SUBROUTINE"){
                if(!in_segment_block){
                    current_type = SEGMENT_TYPE::SUBROUTINE;
                    start_line = i;
                    in_segment_block = true;
                } else {
                    Logging::logWarnMessage("SUBROUTINE Block detected inside another segment block [start=" + std::to_string(start_line+1) + ", end=" + std::to_string(i+1) + "].");
                }
            } else if(useful_statement.substr(0, 8) == "FUNCTION"){
                if(!in_segment_block){
                    current_type = SEGMENT_TYPE::FUNCTION;
                    start_line = i;
                    in_segment_block = true;
                } else {
                    Logging::logWarnMessage("FUNCTION Block detected inside another segment block [start=" + std::to_string(start_line+1)+ ", end=" + std::to_string(i+1) + "].");
                }
            } else if(!in_main_block) {
                in_main_block = true;
                current_type = SEGMENT_TYPE::PROGRAM;
                Logging::logInfoMessage("Entered main program at line " + std::to_string(i + 1));
            }
        }
    }

    if(segment_arr.size() == 0){
        Logging::logWarnMessage("Warning - failed to load a fail program block from file " + file_name);
        Logging::logWarnMessage("Did you forget to include an END Statement?");
    }

    return segment_arr;
}