#ifndef __FILECONTAINER_H_INCLUDED
#define __FILECONTAINER_H_INCLUDED

#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <fstream>
#include "Constants.h"
#include "Globals.h"
#include "Segment.h"
#include "Utils.h"


// The minimum lenght of a line presumed to be correct by the compiler.
#define MINIMUM_LINE_LENGTH 5         
// The string used to indicate a comment  
#define COMMENT_STRING "C"            

 // The length of an 'END' string. 
#define END_STATEMENT_LENGTH 3         
// The length of a 'line label' in FORTRAN, incuding the comment bit
#define LINE_LABEL_LENGTH 6             

 // This starts at 1 - we allow 20 continuations but the first input line counts as #1 
#define CONTINUATION_COUNT_STARTING 1  
// The location in a zero indexed string we must check
 // Fortran Continuations are indicated by placing ANY character in position six. 
#define CONTINUATION_INDICATION_BIT 5   
                                       

class FileContainer {
    public:
        FileContainer(std::string file_name);
        bool expandContinuations();
        std::vector<Segment> dissectSegments();
    private:
        bool lineIsComment(std::string);
        void dumpFileText();
        std::string removeShortLines(std::string input, int line_counter);
        std::string getEnumString(int i);
        std::string removeNewlines(std::string line);

        std::string file_name;
        std::vector<std::string> file_text;
};
#endif