#include "kernel.h"
#include "image.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>

#ifdef _OPENMP
#include <omp.h>
#endif



Kernel::Kernel() : size(0) {}

Kernel::Kernel(const std::string& n, int sz, const std::vector<float>& mat)
    : name(n), size(sz), matrix(mat) {}

bool Kernel::loadFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open kernel file: " << filename << std::endl;
        return false;
    }

    std::getline(file, name);
    if (!name.empty() && name.back() == '\r') name.pop_back();

    std::string sizeLine;
    std::getline(file, sizeLine);
    if (sizeLine.empty() && !file.eof()) {
        std::getline(file, sizeLine);
    }
    size = std::stoi(sizeLine);

    if (size % 2 == 0) {
        std::cerr << "Kernel size must be odd!" << std::endl;
        return false;
    }

    matrix.clear();
    float val;
    for (int i = 0; i < size * size; ++i) {
        if (!(file >> val)) {
            std::cerr << "Not enough values in kernel file (expected " << size * size << ")" << std::endl;
            return false;
        }
        matrix.push_back(val);
    }

    file.close();
    return true;
}

void Kernel::apply(Image& src, Image& dst, BorderStrategy strategy, bool isParallel) const {
    if (matrix.empty() || size == 0) return;

    if (src.width != dst.width || src.height != dst.height || src.channels != dst.channels) {
        dst = Image(src.width, src.height, src.channels);
    }

    int half = size / 2;
    int channels = src.channels;

    auto convolveChannel = [&](int y, int x, int c) {
        float sum = 0.0f;
        for (int ky = -half; ky <= half; ++ky) {
            for (int kx = -half; kx <= half; ++kx) {
                int px = x + kx;
                int py = y + ky;
                unsigned char pixel = src.getPixel(px, py, c, strategy);
                float k = matrix[(ky + half) * size + (kx + half)];
                sum += pixel * k;
            }
        }
        return static_cast<unsigned char>(std::min(255.0f, std::max(0.0f, sum)));
        };

    auto processPixel = [&](int y, int x) {
        for (int c = 0; c < channels; ++c) {
            dst.setPixel(x, y, c, convolveChannel(y, x, c));
        }
        };

    if (isParallel) {
#pragma omp parallel for collapse(2)
        for (int y = 0; y < src.height; ++y) {
            for (int x = 0; x < src.width; ++x) {
                processPixel(y, x);
            }
        }
    }
    else {
        for (int y = 0; y < src.height; ++y) {
            for (int x = 0; x < src.width; ++x) {
                processPixel(y, x);
            }
        }
    }

}


