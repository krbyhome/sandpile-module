#pragma once

#include <deque>
#include <fstream>
#include <string>
#include <vector>

const uint32_t ROW_MULTIPLICITY = 4;
const uint32_t RGB_POWER = 3;

#pragma pack(push, 1)

struct BitMapHeader {
    uint16_t type{0x4D42};
    uint32_t size;
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset{54};
};

#pragma pack(pop)

struct BitMapInfoHeader {
    uint32_t size{40};
    uint32_t width{0};
    uint32_t height{0};
    uint16_t planes{1};
    uint16_t bits_per_pixel{24};
    uint32_t compression{0};
    uint32_t image_size{0};
    uint32_t x_pixels{0};
    uint32_t y_pixels{0};
    uint32_t colors_used{0};
    uint32_t colors_important{0};
};

struct RGB_Colors {
    std::vector<uint8_t> white = {255, 255, 255};
    std::vector<uint8_t> black = {0, 0, 0};
    std::vector<uint8_t> green = {140, 255, 18};
    std::vector<uint8_t> purple = {207, 37, 190};
    std::vector<uint8_t> yellow = {38, 255, 251};
};

std::vector<uint8_t> GetColor(uint64_t value) {
    RGB_Colors colors;
    if (value == 0) {
        return colors.white;
    } else if (value == 1) {
        return colors.green;
    } else if (value == 2) {
        return colors.purple;
    } else if (value == 3) {
        return colors.yellow;
    } else {
        return colors.black;
    }
};

class BitMapFile {
    public:
        void Create(std::deque<std::deque<uint64_t>> net);
        void SavePicture (std::string path, std::string name);
    private:
        BitMapHeader file_header;
        BitMapInfoHeader info_header;
        std::vector <uint8_t> bits;
};
