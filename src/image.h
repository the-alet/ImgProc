#include <opencv2/opencv.hpp>

#include "kernel.h"


#ifndef __image_h__
#define __image_h__


enum BorderStrategy {
    ZERO,    // zero padding
    CLAMP    // clamp to edge
};

class Image {
public:
    int width;
    int height;
    int channels;
    cv::Mat data;   // RGBA image data (CV_8UC4)

    Image();
    Image(int w, int h, int c);

    void input(const char* filename);
    void output(const char* filename);
    void process(void (*kernelFunc)(Image&, Image&, Kernel&, BorderStrategy, bool), Image& result, Kernel& kernel, BorderStrategy strategy, bool isParallel);

    unsigned char getPixel(int x, int y, int c, BorderStrategy strategy) const;
    void setPixel(int x, int y, int c, unsigned char value);
};

#endif // __image_h__