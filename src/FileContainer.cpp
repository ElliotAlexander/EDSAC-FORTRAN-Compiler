#include "FileContainer.h"


/**
 * 
 *          Class FileContainer:
 *          
 *          Member Variables:
 *                  std::string file_name;  -> initialised in the constructor
 *                  std::vector<std::string> -> loaded from file file_name in the constructor.
 * 
 * 
 **/


// FileContainer::FileContainer(std::string file_name_in);
// @param file_name_in - the name of the input file the FileContainer object represents.
// FileContainer is a 1:1 relationship between an input file and it's representation in the program. 
// each FileContainer is a container for one specific file. 
// The constructor loads the file into a std::vector<std::string> stored as a member variable.
FileContainer::FileContainer(std::string file_name_in) : file_name(file_name_in){
    std::ifstream input(FileContainer::file_name);                                                // Open an input stream to the file specified
    std::string line_buffer_temp;                                                   // Declare a temporary variable to store each line in.
    int line_counter_temp = 1;                                                      // Initialised a temporary variable to keep track of a line count in.

    while( std::getline( input, line_buffer_temp ) ) {                              // Iterate through the whole file.
        line_buffer_temp = removeShortLines(line_buffer_temp, line_counter_temp);        // if a line is too short, remove it and mark it as a comment (where line length < MINIMUM_LINE_LENGTH)
        line_buffer_temp = removeNewlines(line_buffer_temp);                        // If a line is blank, remove it and mark it as a comment.
        FileContainer::file_text.push_back(line_buffer_temp);                       // Build a member variable of the complete file text.
        line_counter_temp++;                                                        // update line counter.
    }

    if(Globals::dump_data_structures){                                              // enabled through a commmand line flag, dump the file to the command line if required.
        dumpFileText();
    }
}


// std::vector<Segment> FileContainer::dissectSegments(){
// @return std::vector<Segment> - The built list of Segment objects contained within the file represented by the FileContainer object.
// This function breaks down the program text contained in the member variable file_text into a list of Segment objects.
// This function does not change class state
std::vector<Segment> FileContainer::dissectSegments(){

    std::vector<Segment> segment_arr;                   // Return variable - to be constructed
    bool in_function_or_subroutine_block = false;       // Start outside a segment, the first line of the file willl input
    bool in_main_block = true;                          // Start inside the main program block, remain there until we see a FUNCTION or SUBROUTINE statement.
    SEGMENT_TYPE current_type = {};                     // Indicating the current type of segment we are inside, FUNCTION, SUBROUTINE or MAIN PROGRAM.
    int start_line = 0;


    /**
     *  This loop iterates through each line in the file text
     *  The loop tracks which a) type of segment it is currently in b) if it is currently in a segment c) where the current segment started
     *  At the end of each segment (i.e. when a return or END statement is seen) the loop backtracks, builds a string vector of all the lines in that segment (since the starting line), and then builds a segment object with this list
     *  Once a segment object is built, it is added to segment_arr, the return value for the whole function.
     * This algorithm hence breaks down the file into a list of segments, and warns the user when they try to do things they shouldn't either outside of a segment or in the wrong segment type
     * */   

    for(std::vector<std::string>::size_type i = 0; i != FileContainer::file_text.size(); i++) {
        if(!::lineIsComment(FileContainer::file_text[i])){             // Skip comments
            std::string useful_statement = FileContainer::file_text[i].substr(LINE_LABEL_LENGTH, FileContainer::file_text[i].length());                                                                // Set the program text to a local variable. Ignore the line label i.e. chars 0 -> 6
            if(useful_statement.substr(0,END_STATEMENT_LENGTH) == "END" && useful_statement.length() == END_STATEMENT_LENGTH){                                          // If the line is an END statement. Note that there might be possible problems here with ENDVARIABLE, for example.
                if(in_function_or_subroutine_block){   // END should signify the END of the program as a whole. If we're inside a segment, the prgorammer needs to RETURN first. This only applies to FUNCTION and SUBROUTINE blocks, as the MAIN program can exit without a return.
                    Logging::logErrorMessage( "END statement found inside a segment block. Are you missing a return? [" + std::to_string(i) + "].");
                } else if(in_main_block){       // If we're inside the main priogra
                    in_main_block = false;      // Leave the main block
                    std::vector<std::string> segment_text;                  // Begin building a list of thee lines inside that segment.
                    for(int x = start_line; x < ( i+1 ); x++){              // For each line in the segment
                        segment_text.push_back(FileContainer::file_text.at(x));            // Add it to a list
                    }
                    Logging::logMessage("+" + ::getEnumString(SEGMENT_TYPE::PROGRAM) + " [" + std::to_string(start_line + 1) + "," + std::to_string(i + 1) + "]");  // output to the user.
                    segment_arr.push_back(Segment(SEGMENT_TYPE::PROGRAM, start_line, i, segment_text));  // Build a segment with our list of strings, add it to the overarching data structure.
                } else {
                    Logging::logWarnMessage("END detected outside of Main Program Block[" + std::to_string(i) + "]");           // THis should only catch if the program starts with END.
                }
            } else if(useful_statement.substr(0, 6) == "RETURN") {
                if(in_function_or_subroutine_block){            // If we're not in a function or subroutine block, we can't call return. Throw the user an error if they try this.
                    std::vector<std::string> segment_text;      // Build an array of the program lines in this segment
                    for(int x = start_line; x < ( i+1 ); x++){  // iterate through the segment
                        segment_text.push_back(FileContainer::file_text.at(x));// Add each line to the array
                    }

                    Logging::logInfoMessage("+" + ::getEnumString(current_type) + " [" + std::to_string(start_line + 1) + "," + std::to_string(i + 1) + "]{" + ::stripWhitespaceString(segment_text.at(0)) + "}.");
                    
                    segment_arr.push_back(Segment(current_type, start_line, i, segment_text));      // Construct a segment object, add it back to our return array. This segment is now finished with.
                    in_function_or_subroutine_block = false;    // We are no longer in a function or subroutine block, the user has just exited this by calling return.
                    start_line = i+1;                           // Reset the segment start line counter.
                    current_type = {};                          // Reset the segment type counter. 
                } else {
                    Logging::logWarnMessage("RETURN detected outside of Subroutine Block [start=" + std::to_string(start_line + 1) +  ", end=" + std::to_string(i+1) +  "].");      // if we're in the main program block - the user should not be calling return.
                }
            } else if(useful_statement.substr(0, 10) == "SUBROUTINE"){  
                if(!in_function_or_subroutine_block){           // Nested subrutines / functions aren't allowed - so we should never see this statement inside another function or subroutine.
                    current_type = SEGMENT_TYPE::SUBROUTINE;    // Set current type
                    start_line = i;                             // Set start line - once we see a RETURN statement, we'll iterate from this line down and build the segment.
                    in_function_or_subroutine_block = true;     
                } else {
                    Logging::logWarnMessage("SUBROUTINE Block detected inside another segment block [start=" + std::to_string(start_line+1) + ", end=" + std::to_string(i+1) + "].");
                }
            } else if(useful_statement.substr(0, 8) == "FUNCTION"){ 
                if(!in_function_or_subroutine_block){           // Nested subroutines / functions aren't allowed - we should never see this statemenet when inside another function or subroutine 
                    current_type = SEGMENT_TYPE::FUNCTION;      // Set current segmetn type 
                    start_line = i;                             // Set start line - we'll iterate from this to the end of the function once we see it
                    in_function_or_subroutine_block = true;     // 
                } else {
                    Logging::logWarnMessage("FUNCTION Block detected inside another segment block [start=" + std::to_string(start_line+1)+ ", end=" + std::to_string(i+1) + "].");
                }
            } else if(!in_main_block) {                 // If we're not in the main block, and see a statement that isn't already specified - enter the main block!
                in_main_block = true;                   //
                current_type = SEGMENT_TYPE::PROGRAM;   // 
                Logging::logInfoMessage("Entered main program at line " + std::to_string(i + 1));
            }
        }
    }


    // If we find a segment with no statements in it - warn the user.
    // This also catches non-terminated segments - i.e. a Main Program segment without an END.
    if(segment_arr.size() == 0){
        Logging::logWarnMessage("Warning - failed to load a fail program block from file " + file_name);
        Logging::logWarnMessage("Did you forget to include an END Statement?");
    }


    // Returns std::vector<Segment> -> built inside above for loop.
    return segment_arr;
}

// void FileContainer::dumpFileText() 
//
//
// This function takes and returns no arguments
// the purpose of this function is to dump + format the file text to the command line.
// This is activated upon a user enabled command line flag. 
// The file text is loaded and constructed in the constructor.
void FileContainer::dumpFileText(){
    Logging::logMessage("Begin File Dump(Name=" + file_name + "):\n");                                  // Pretty printing
    for (std::vector<std::string>::const_iterator i = FileContainer::file_text.begin(); i != FileContainer::file_text.end(); ++i)     //
        Logging::logMessage(*i + ' ');                                                                  // For each - print that line with no formmatting.
    Logging::logMessage("\nEnd File Dump\n");
}


// bool FileContainer::expandContinuations()
//
// @return bool -> indicates success / failure.
// @member file_text  
//
// This function modifies class state
// This function iterates through the member variable file_text, removing continuations and appending them into a single line.
// The continuation lines removed as replaced by comments.
// This modification is done *in place* inside FileContainer::file_text.
bool FileContainer::expandContinuations(){
    int continuation_count = CONTINUATION_COUNT_STARTING;
    for(std::vector<std::string>::size_type i = 0; i != FileContainer::file_text.size(); i++) {             // Iterate through file text
        if(!::lineIsComment(FileContainer::file_text[i])){             // Ignore comments in the file text - they cannot be continuations.
            if(continuation_count == 20) {          // FAIL - if over 20 consecutive continuations have been seen.
                Logging::logErrorMessage("Over 20 Continuations detected! Aborting. Line[" + std::to_string(i-19) + "]{'" + FileContainer::file_text[i-continuation_count] + "'}.");
                return false;                       // Exit with an error - return this to the calling class.
            } else if(                              // SUCCESS - The line is marked as a continuation
                    ( FileContainer::file_text[i].at(CONTINUATION_INDICATION_BIT) != ' ')     // Continuations are indicated by placing ANY character in position 6 (zero indexed)
                    && (i != 0))                                              // A continuation cannot be on the first line of the file
            {
                if( FileContainer::file_text[i].substr(0,4).find_first_not_of(' ') != std::string::npos){                   // Continuations cannot be line labels. Warn the user and abort if it is.
                    Logging::logErrorMessage("Line {'" + FileContainer::file_text[i] + "'}[" + std::to_string(i+1) + "] is marked as a continuation, but contains a label. Aborting.");
                    return false;           // Exit to the calling class.
                } else {
                    std::string line_text_backup = FileContainer::file_text[i];            // Make a copy of the line we're modifying - in case we need to print it later.
                    FileContainer::file_text[i].erase(0,6);                                // This MUST be empty - so it can be removed. This includes deleting the continuation character.
                    if(FileContainer::file_text[i].length() == 0){                         // Check that the rest of the line is not zero.
                        Logging::logErrorMessage("Empty continuation - Continuation labelled lines must contained at least one character.");
                        ::printErrorLocation(7, line_text_backup);          // Print an error - note use case of previous backup.
                    } else {
                        FileContainer::file_text[i-continuation_count] += FileContainer::file_text[i];    // Append continuation to prervious non-continuation line, forming one longer line.
                        FileContainer::file_text[i] = std::string("C");                    // Mark the line IN PLACE as a blank comment
                        continuation_count += 1;                            // Keep track of the number of continuations we've seen.
                    }
                }
            } else {
                continuation_count = 1;                                     // If the line is not a continuation - reset the continuation count.
            }
        }
    }
    return true;        // Success - output was modified in place. 
}

// std::string FileContainer::removeNewlines(std::string line)
//
// @param an input line - a single line input which will have it's newline characters removed.
// @return The modified input line, with all CR LF characters removed
//
//This function acts as a utility class - it has no impact on class state nor does it use any member variables.
//
std::string FileContainer::removeNewlines(std::string line){
    std::string::size_type pos = 0;                                 // iterate from position zero
    while ( ( pos = line.find ("\r",pos) ) != std::string::npos )   // Find all \r characters, remove them.
    {
        line.erase ( pos, 2 );      
    } 

    pos = 0;                                                        // Repeat this process for \r\n
    while ( ( pos = line.find ("\r\n",pos) ) != std::string::npos ) //
    {
        line.erase ( pos, 2 );
    } 
    return line;                                                    // Return the modified line.
}


// std::string FileContainer::removeShortLines(std::string line, int line_counter)
// 
// @param std::string line - the input line to check
// @param int line_counter - The line number - used for error messages. 
//
// This function takes an input line, check's it's length and informs the user if it's too short
// If the line is of a proper length, it's returned to the calling class intact. 
// If the line is too shorrt, it's marked as a COMMENT and returned to the calling class alongside an error message to the user.
std::string FileContainer::removeShortLines(std::string line, int line_counter){
        // If line length warnings are enabled, warn the user on lines < 5 chars long.
        if((line.length() < MINIMUM_LINE_LENGTH) && !(::lineIsComment(line))) {
            Logging::logWarnMessage("Line { " + line + " }[" + std::to_string(line_counter) + "] has an unusually short length. It will be marked as a comment and ignored.");
            line.insert(0, COMMENT_STRING);
        }
        return line;
}