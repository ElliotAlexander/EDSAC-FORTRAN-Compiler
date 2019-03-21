#include "Segment.h"

Segment::Segment(SEGMENT_TYPE input_seg_type, int start_line, int end_line, std::vector<std::string> input_segment_body) : 
    seg_type(input_seg_type), 
    segment_body(input_segment_body),
    start_line(start_line),
    end_line(end_line)
{
    if(Globals::dump_data_structures){
        dumpSegment();
    }
}

std::vector<Statement*>  Segment::buildStatements(){
    for(std::vector<std::string>::size_type i = 0; i != segment_body.size(); i++){ 
        if(!::lineIsComment(segment_body[i])){
            std::string label = segment_body[i].substr(0,5);
            std::string statement_body = segment_body[i].substr(6, segment_body[i].length());
            Statement* stmt = new Statement(statement_body, label, i + start_line);
            statement_arr.push_back(stmt);
        }
    }

    return statement_arr;
}

void Segment::dumpSegment(){
    Logging::logMessage("Begin Segment Dump(Type=" + ::getEnumString(seg_type) + ")");
    for(std::vector<std::string>::size_type i = 0; i != segment_body.size(); i++){ 
        Logging::logMessage(segment_body[i]);
    }
    Logging::logMessage("End Segment Dump ");
}


SEGMENT_TYPE Segment::getSegmentType(){
    return Segment::seg_type;
}

int Segment::getLineLabel(){
    return Segment::start_line;
}