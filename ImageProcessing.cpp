#include <opencv2/core/mat.hpp>
#include "ImageProcessing.h"
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

cv::Mat ImageProc::openImage(std::string path)
{
    cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);
    return img;
}

cv::Mat ImageProc::stripChannel(cv::Mat& img, char channel) {
    cv::Mat targetChannel;
    std::size_t ch;
    if (channel == 'b') {
        ch = 0;
    }
    else if (channel == 'g') {
        ch = 1;
    }
    else {
        ch = 2;
    }
    std::vector<cv::Mat> channels(3);
    // split img:
    split(img, channels);
    // get the channels (follow BGR order in OpenCV)
    channels[ch] = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
    merge(channels, img);
    return img;
}

cv::Mat ImageProc::toBW(cv::Mat& img, std::size_t threshold) {
    // Convert to grayscale
    cv::Mat im_gray;
    cv::cvtColor(img, im_gray, cv::ColorConversionCodes::COLOR_RGB2GRAY);
    // Convert to b and w with the given threshold.
    cv::Mat img_bw = im_gray > threshold;
    return img_bw;
}

cv::Mat ImageProc::crop(cv::Mat& img, std::size_t x, std::size_t y, std::size_t width, std::size_t height) {
    return img(cv::Range(y, y + height), cv::Range(x, x + width)); // Slicing to crop the image

}

cv::Mat ImageProc::boostColor(cv::Mat& img, std::size_t blue, std::size_t green, std::size_t red, std::size_t radius) {
    cv::Mat filteredImg;
    cv::inRange(img, cv::Scalar(blue - radius, green - radius, red - radius), cv::Scalar(blue + radius, green + radius, red + radius), filteredImg);
    return filteredImg;
}