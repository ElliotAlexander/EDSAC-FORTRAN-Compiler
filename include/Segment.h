#ifndef __SEGMENT_H_INCLUDED
#define __SEGMENT_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <vector>

#include "Statement.h"
#include "Utils.h"
#include "Globals.h"

enum SEGMENT_TYPE
{
    FUNCTION = 0, 
    PROGRAM = 1,
    SUBROUTINE = 2
};


class Segment {
    public:
        Segment(SEGMENT_TYPE input_seg_type, int start_line, int end_line, std::vector<std::string> input_statement_body);
        void dumpSegment();
    private:
        SEGMENT_TYPE seg_type;
        std::vector<std::string> segment_body;
        std::vector<Statement> statement_arr;
};

#endif