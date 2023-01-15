#pragma once

#include "../bmp/bmp.cpp"
#include "../opt/console_parser.h"

#include <algorithm>
#include <deque>
#include <fstream>
#include <vector>

struct cell;

class sandpile {
    public:
        void BuildNet(uint16_t length, uint16_t width, const std::string& path);
        void Collapse(const options& opts);
        void Expansion(std::string expansion, size_t& y, size_t& x);
        std::string CheckForExpansion(size_t y, size_t x);
    private:
        std::deque<std::deque<uint64_t>> net;
        std::deque<uint64_t> current_line;
        std::deque<uint64_t> next_line;
};
