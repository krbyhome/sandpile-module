#include "sandpile.h"

struct cell {
    uint16_t x;
    uint16_t y;
    uint64_t value;
};

void sandpile::BuildNet(uint16_t length, uint16_t width, const std::string& path) {
    std::ifstream get_sand(path);
    cell sand;
    std::vector<cell> input;
    while(get_sand >> sand.x) {
        get_sand >> sand.y;
        get_sand >> sand.value;
        input.emplace_back(sand);
    }
    for (size_t i = 0; i < width; i++) {
        net.push_back({});
        for (size_t j = 0; j < length; j++) {
                net[i].push_back(0);
        }
    }
    for (size_t i = 0; i < input.size(); i++) {
        net[input[i].y - 1][input[i].x - 1] = input[i].value;
    }
}

std::string sandpile::CheckForExpansion(size_t y, size_t x) {
    if (y == 0) {
        return "up";
    } else if (y + 1 == net.size()) {
        return "down";
    } else if (x == 0) {
        return "left";
    } else if (x + 1 == net[y].size()) {
        return "right";
    } else {
        return "No need";
    }
}

void sandpile::Expansion(std::string expansion, size_t& y, size_t& x) {
    if (expansion == "up") {
        uint32_t length = net[0].size();
        net.push_front({});
        for (uint32_t i = 0; i < length; i++) {
            net[0].push_back(0);
        }
        y++;
    } else if (expansion == "down") {
        uint32_t length = net[0].size();
        net.push_back({});
        for (uint32_t i = 0; i < length; i++) {
            net[net.size() - 1].push_back(0);
        }
    } else if (expansion == "left") {
        current_line.push_front(0);
        next_line.push_front(0);
        for (uint32_t i = 0; i < net.size(); i++) {
            net[i].push_front(0);
        }
        x++;
    } else if (expansion == "right") {
        current_line.push_back(0);
        next_line.push_back(0);
        for (uint32_t i = 0; i < net.size(); i++) {
            net[i].push_back(0);
        }
    }
}

void sandpile::Collapse(const options& opts) {
    bool stable = false;
    int pics_created = 0;
    current_line.resize(net[0].size(), 0);
    next_line.resize(net[0].size(), 0);
    for (uint64_t k = 0; k < opts.max_iter && !stable; k++) {
        stable = true;
        for (size_t y = 0; y < net.size(); y++) {
            for (size_t x = 0; x < net[y].size(); x++) {
                if (net[y][x] > 3) {
                    stable = false;
                    std::string expansion = CheckForExpansion(y, x);
                    if (expansion != "No need") {
                        Expansion(expansion, y, x);
                    }
                    net[y][x] -= 4;
                    net[y - 1][x]++;
                    net[y][x - 1]++; 
                    next_line[x]++;
                    current_line[x + 1]++;
                    net[y][x] += current_line[x];
                    current_line[x] = 0;
                } else {
                    net[y][x] += current_line[x];
                    current_line[x] = 0;
                }
            }
            std::swap(current_line, next_line);
            next_line.resize(net[y].size(), 0);
        }
        if (opts.freq != 0 && k % opts.freq == 0) {
            pics_created++;
            BitMapFile picture;
            picture.Create(net);
            std::string name = std::to_string(pics_created) + ".bmp";
            picture.SavePicture(opts.output_path, name);
        }
    }
    if (opts.freq == 0) {
        BitMapFile picture;
        picture.Create(net);
        std::string name = "1.bmp";
        picture.SavePicture(opts.output_path, name);
    }
}
