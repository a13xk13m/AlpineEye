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

cv::Mat ImageProc::inverse(cv::Mat& img) {
    cv::Mat inversedImg;
    cv::bitwise_not(img, inversedImg);
    return inversedImg;
}

cv::Mat ImageProc::denoise(cv::Mat& img, double threshold, std::size_t passes)  {
    for (int p = 0; p < passes; ++p) {
        for (int r = 0; r < img.rows; r++) {
            uchar* ptr = img.ptr<uchar>(r);
            for (int c = 0; c < img.cols; c++) {
                // Check if pixel is black.
                if (img.ptr(r)[c] == 0) {
                    int count = 0;
                    // Create frame around pixel if the the pixel is black.
                    const int radius = 1;
                    const int width = radius * 2 + 1;
                    for (int i = radius * -1; i < width; i++) {
                        for (int j = radius * -1; j < width; j++) {
                            if (r + i > 0 && r + i < img.rows) {
                                if (c + j > 0 && c + j < img.cols) {
                                    uchar pixel = img.ptr<uchar>(r + i)[c + j];
                                    if (pixel == 0) {
                                        count++;
                                    }
                                }
                            }
                        }
                    }
                    if (count < width * width * threshold) {
                        img.ptr(r)[c] = 255;
                    }
                }
            }
        }
    }
    return img;

}