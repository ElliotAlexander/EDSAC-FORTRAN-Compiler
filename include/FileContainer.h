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

        std::vector<Segment> segment_arr;
};
#endif