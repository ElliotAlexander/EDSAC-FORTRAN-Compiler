#include "Segment.h"

/**
 * 
 *   Class Sgement:
 *   
 *   Member Variables:
 *           int start_line -> The start line of the segment in the input file.
 *           int end_line   -> The end line of the segment in the input file.
 *           SEGMENT_TYPE seg_type -> The type of the segment {FUNCTION, PROGRAM, SUBROUTINE}. Accessed with a getter.
 *           std::vector<std::string> segment_body -> The complete text of the segment, including comments and continuations expanded.
 *           std::vector<Statement> statement_arr -> The complete text of the segment wrapped in Statement objects. This represents the first
 *                  stage of an internal representation.
 **/



Segment::Segment(SEGMENT_TYPE input_seg_type, int start_line, int end_line, std::vector<std::string> input_segment_body) : 
    seg_type(input_seg_type), 
    segment_body(input_segment_body),
    start_line(start_line),
    end_line(end_line)
{
    if(Globals::dump_data_structures){      // Enabled from the command line
        dumpSegment();                      // Print the whole text of each segment.
    }
}


// std::vector<Statement*>  Segment::buildStatements()
//
// @return std::vector<Statement> -> Build the file text into an internal representation of Statements.
// 
// This file serves as a secondary constructor, calleed after the class has initialised. This enables the whole
// file to be processed line by linee, before statement objects are constructed and tokenization begins.
// 
// This function modifies the internal state of the class. 
// This function also serves as the only accessor to Segment::statement_arr, so it cannot be accessed before being
// initialised by external actors. 
std::vector<Statement*>  Segment::buildStatements(){
    for(std::vector<std::string>::size_type i = 0; i != segment_body.size(); i++){  // For each statement
        if(!::lineIsComment(segment_body[i])){                                      // There is no provision in the internal representation for comments.
            std::string label = segment_body[i].substr(0,5);                        // Disect label and statement body. Ignore Continuation character.
            std::string statement_body = segment_body[i].substr(6, segment_body[i].length());
            Statement* stmt = new Statement(statement_body, label, i + start_line); // Initialise internal representation
            statement_arr.push_back(stmt);                                          // Build return value
        }
    }
    return statement_arr;
}


// void Segment::dumpSegment() 
//
// This function outputs the segment as a string.
// Note that this function has no interaction with statement_arr.
// 
void Segment::dumpSegment(){
    Logging::logMessage("Begin Segment Dump(Type=" + ::getEnumString(seg_type) + ")");      // Get enum string convets the segment type enum to a string.
    for(std::vector<std::string>::size_type i = 0; i != segment_body.size(); i++){ 
        Logging::logMessage(segment_body[i]);
    }
    Logging::logMessage("End Segment Dump ");
}

// SEGMENT_TYPE Segment::getSegmentType()
//
// @return SEGMENT_TYPE 
//
// STUB getter method for seg_type.
//
SEGMENT_TYPE Segment::getSegmentType(){
    return Segment::seg_type;
}

