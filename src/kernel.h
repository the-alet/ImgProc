#pragma once

#include <string>
#include <vector>

#include "image.h"

#ifndef __kernel_h__
#define __kernel_h__

class Kernel {
public:
    std::string name;
    int size;
    std::vector<float> matrix;

    Kernel();
    Kernel(const std::string& n, int sz, const std::vector<float>& mat);

    bool loadFromFile(const char* filename);
    void apply(Image& src, Image& dst, BorderStrategy strategy, bool parallel = false) const;
};

#endif // __kernel_h__