#include "opt/console_parser.h"
#include "sandpile_lib/sandpile.h"

int main(int argc, const char** argv) {
    options opts;
    opts.ProccessOpts(argc, argv);
    opts.Print();
    sandpile heap;
    heap.BuildNet(opts.length, opts.width, opts.input_path);
    heap.Collapse(opts);

    return 0;
}
