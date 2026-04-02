#include <iostream>
#include <algorithm>

#include "image.h"
#include "kernel.h"

Image::Image() : width(0), height(0), channels(0) {}

Image::Image(int w, int h, int c) : width(w), height(h), channels(c) {
    data = cv::Mat(h, w, CV_MAKETYPE(CV_8U, c));
    data.setTo(0);
}

void Image::input(const char* filename) {
    cv::Mat img = cv::imread(filename, cv::IMREAD_UNCHANGED);
    if (img.empty()) {
        std::cerr << "Error loading image: " << filename << std::endl;
        return;
    }
    if (img.channels() != 4) {
        cv::cvtColor(img, img, cv::COLOR_BGR2RGBA);
    }
    data = img.clone();
    width = data.cols;
    height = data.rows;
    channels = data.channels();
}

void Image::output(const char* filename) {
    if (data.empty()) return;
    cv::imwrite(filename, data);
}

void Image::process(void (*kernelFunc)(Image&, Image&, Kernel&, BorderStrategy, bool), Image& result, Kernel& kernel, BorderStrategy strategy, bool isParallel) {
    kernelFunc(*this, result, kernel, strategy, isParallel);
}

unsigned char Image::getPixel(int x, int y, int c, BorderStrategy strategy) const {
    switch (strategy) {
    case ZERO:
        if (x < 0 || x >= width || y < 0 || y >= height)
            return 0;
        return data.at<cv::Vec4b>(y, x)[c];
    case CLAMP:
        x = std::max(0, std::min(x, width - 1));
        y = std::max(0, std::min(y, height - 1));
        return data.at<cv::Vec4b>(y, x)[c];
    default:
        return 0;
    }
}

void Image::setPixel(int x, int y, int c, unsigned char value) {
    if (x >= 0 && x < width && y >= 0 && y < height && c >= 0 && c < channels)
        data.at<cv::Vec4b>(y, x)[c] = value;
}