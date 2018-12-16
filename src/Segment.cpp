#include "Segment.h"

Segment::Segment(SEGMENT_TYPE input_seg_type, int start_line, int end_line, std::vector<std::string> input_segment_body){
    seg_type = input_seg_type;
    segment_body = input_segment_body;

    for(std::vector<std::string>::size_type i = 0; i != segment_body.size(); i++){ 
        if(!::lineIsComment(segment_body[i])){
            std::string label = segment_body[i].substr(0,4);
            std::string statement_body = segment_body[i].substr(5, segment_body.size() - 1);
            statement_arr.push_back(Statement(statement_body, label, i + start_line));
        }
    }

    if(Globals::dump_data_structures){
        dumpSegment();
    }
}

void Segment::dumpSegment(){
    std::cout << "\n:: Begin Segment Dump :: (Type=" << ::getEnumString(seg_type) << ") :: \n\n";
    for(std::vector<std::string>::size_type i = 0; i != segment_body.size(); i++){ 
        std::cout << segment_body[i] << std::endl;
    }
    std::cout << "\n:: End Segment Dump :: \n" << std::endl;
}