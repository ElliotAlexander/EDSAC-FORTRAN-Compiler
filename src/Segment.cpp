#include "Segment.h"

Segment::Segment(SEGMENT_TYPE input_seg_type, int start_line, int end_line, std::vector<std::string> input_segment_body){
    seg_type = input_seg_type;
    segment_body = input_segment_body;
    Segment::start_line = start_line;
    Segment::end_line = end_line;

    if(Globals::dump_data_structures){
        dumpSegment();
    }
}

std::vector<Statement>  Segment::buildStatements(){
    for(std::vector<std::string>::size_type i = 0; i != segment_body.size(); i++){ 
        if(!::lineIsComment(segment_body[i])){
            std::string label = segment_body[i].substr(0,4);
            std::string statement_body = segment_body[i].substr(6, segment_body[i].length());
            Statement stmt(statement_body, label, i + start_line);
            statement_arr.push_back(stmt);
        }
    }

    return statement_arr;
}

void Segment::dumpSegment(){
    std::cout << "Begin Segment Dump(Type=" << ::getEnumString(seg_type) << ")\n";
    for(std::vector<std::string>::size_type i = 0; i != segment_body.size(); i++){ 
        std::cout << segment_body[i] << std::endl;
    }
    std::cout << "End Segment Dump \n" << std::endl;
}