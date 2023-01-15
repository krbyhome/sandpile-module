#include "bmp.h"

void BitMapFile::Create(std::deque<std::deque<uint64_t>> net) {
        info_header.width = net[0].size();
        info_header.height = net.size();
        uint32_t padding_row = (ROW_MULTIPLICITY - (RGB_POWER * info_header.width) % ROW_MULTIPLICITY) % ROW_MULTIPLICITY;
        for (size_t i = 1; i <= net.size(); i++) {
            for (size_t j = 0; j < info_header.width; j++) {
                std::vector<uint8_t> color;
                color = GetColor(net[net.size() - i][j]);
                for (size_t k = 0; k < RGB_POWER; k++) {
                    bits.push_back(color[k]);
                }
            }
            for (size_t j = 0; j < padding_row; j++) {
                bits.push_back(0);
            }
        }
        file_header.size = file_header.offset + bits.size();
}

void BitMapFile::SavePicture(std::string path, std::string name) {
    std::string full_path = path + "/" + name;
    std::ofstream output(full_path, std::ios_base::binary);
    output.write((const char*)& file_header, sizeof(file_header));
    output.write((const char*)& info_header, sizeof(info_header));
    output.write((const char*) bits.data(), bits.size());
}
