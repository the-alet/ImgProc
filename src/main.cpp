#include <iostream>
#include <string>

#include "image.h"
#include "kernel.h"

static void applyKernel(Image& src, Image& dst, Kernel& kernel, BorderStrategy strategy, bool isParallel) {
    kernel.apply(src, dst, strategy, isParallel);
}

int main(int argc, char* argv[]) {

    static Kernel currentKernel;
    static BorderStrategy strategy = ZERO;
    static bool isParallel = false;

    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <input_image> <output_image> --kernel=<kernel_file> [--border=<zero|clamp>] [--parallel=<true|false>]\n";
        std::cout << "  --kernel      : path to kernel file (required)\n";
        std::cout << "  --border      : border handling strategy (zero or clamp, default: zero)\n";
        std::cout << "  --parallel    : enable parallel execution (true or false, default: false)\n";
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    std::string kernelFile;
    std::string borderStr = "zero";
    std::string parallelStr = "false";

    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.find("--kernel=") == 0) {
            kernelFile = arg.substr(9);
        }
        else if (arg.find("--border=") == 0) {
            borderStr = arg.substr(9);
        }
        else if (arg.find("--parallel=") == 0) {
            parallelStr = arg.substr(11);
        }
    }

    if (kernelFile.empty()) {
        std::cerr << "Error: kernel file not specified. Use --kernel=<filename>" << std::endl;
        return 1;
    }

    if (!currentKernel.loadFromFile(kernelFile.c_str())) {
        return 1;
    }

    if (borderStr == "clamp") {
        strategy = CLAMP;
    }
    else if (borderStr == "zero") {
        strategy = ZERO;
    }
    else {
        std::cerr << "Invalid border strategy: " << borderStr << ". Use --border=<zero|clamp>" << std::endl;
        return 1;
    }

    if (parallelStr == "true") {
        isParallel = true;
    }
    else if (parallelStr == "false") {
        isParallel = false;
    }
    else {
        std::cerr << "Invalid parallel flag: " << parallelStr << ". Use --parallel=<true|false>" << std::endl;
        return 1;
    }

    Image img;
    img.input(inputFile.c_str());

    Image result(img.width, img.height, img.channels);
    img.process(applyKernel, result, currentKernel, strategy, isParallel);
    result.output(outputFile.c_str());

    std::cout << "Processing completed. Result saved to " << outputFile << std::endl;
    return 0;
}