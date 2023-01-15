#include "console_parser.h"

void options::Print() {
    std::cout << "length: " << length << "\n";
    std::cout << "width: " << width << "\n";
    std::cout << "input from " << input_path << "\n";  
    std::cout << "output to " << output_path << "\n";
    std::cout << "maximum iterations: " << max_iter << "\n";
    std::cout << "frequency: " << freq << "\n";
}

void options::ProccessOpts(int args, const char**& console_line) {
    std::string current_opt;
    for (int i = 1; i < args; i++) {
        current_opt = console_line[i];
        if (current_opt == "-l" || current_opt == "--length") {
            length = std::stoi(console_line[i + 1]);
        } else if (current_opt == "-w" || current_opt == "--width") {
            width = std::stoi(console_line[i + 1]);
        } else if (current_opt == "-i" || current_opt == "--input") {
            input_path = console_line[i + 1];
        } else if (current_opt == "-o" || current_opt == "--output") {
            output_path = console_line[i + 1];
        } else if (current_opt == "-m" || current_opt == "--max-iter") {
            max_iter = std::stoi(console_line[i + 1]);
        } else if (current_opt == "-f" || current_opt == "--freq") {
            freq = std::stoi(console_line[i + 1]);
        }
    }
}
