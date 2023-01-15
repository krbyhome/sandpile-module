#pragma once

#include <iostream>
#include <string>

class options {
    public:
        uint16_t length;
        uint16_t width;
        std::string input_path;
        std::string output_path;
        uint64_t max_iter;
        uint64_t freq;
    
        void Print();
        void ProccessOpts(int args, const char**& console_line);

        options(): length(10), width(10), input_path("input.txt"),  output_path("C:/bitmaps3"), max_iter(1000000), freq(5000) {};
};
