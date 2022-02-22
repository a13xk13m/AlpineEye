#include <opencv2/core/mat.hpp>
#include "ImageProcessing.h"
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

cv::Mat ImageProc::openImage(std::string path)
{
    cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);
    return img;
}

void ImageProc::crop(cv::Mat& img, std::size_t x, std::size_t y, std::size_t width, std::size_t height) {
    img = img(cv::Range(y, y + height), cv::Range(x, x + width)); // Slicing to crop the image

}

void ImageProc::boostColor(cv::Mat& img, std::size_t blue, std::size_t green, std::size_t red, std::size_t radius) {
    cv::Mat filteredImg;
    cv::inRange(img, cv::Scalar(blue - radius, green - radius, red - radius), cv::Scalar(blue + radius, green + radius, red + radius), filteredImg);
    img = filteredImg;
}
