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

void ImageProc::stripChannel(cv::Mat& img, char channel) {
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
}

void ImageProc::toBW(cv::Mat& img, std::size_t threshold) {
    // Convert to grayscale
    cv::Mat im_gray;
    cv::cvtColor(img, im_gray, cv::ColorConversionCodes::COLOR_RGB2GRAY);
    // Convert to b and w with the given threshold.
    img = im_gray > threshold;
}

void ImageProc::crop(cv::Mat& img, std::size_t x, std::size_t y, std::size_t width, std::size_t height) {
    img = img(cv::Range(y, y + height), cv::Range(x, x + width)); // Slicing to crop the image

}

void ImageProc::boostColor(cv::Mat& img, std::size_t blue, std::size_t green, std::size_t red, std::size_t radius) {
    cv::Mat filteredImg;
    cv::inRange(img, cv::Scalar(blue - radius, green - radius, red - radius), cv::Scalar(blue + radius, green + radius, red + radius), filteredImg);
    img = filteredImg;
}

void ImageProc::inverse(cv::Mat& img) {
    cv::Mat inversedImg;
    cv::bitwise_not(img, inversedImg);
    img = inversedImg;
}

void ImageProc::denoise(cv::Mat& img, const int kernelSize)  {
    int halfSize{ kernelSize / 2 };
    int pos = { kernelSize * kernelSize / 2 };
    uchar* p;
    for (int r = 0; r < img.rows; r++) {
        for (int c = 0; c < img.cols; c++) {
            std::vector<uchar> frame(kernelSize * kernelSize);

            // Iterate through the frame.
            for (int x = { -halfSize }; x <= halfSize; x++)
            {
                for (int y = { -halfSize }; y <= halfSize; y++)
                {
                    if (c + x > img.cols && c + x < 0 && r + x > img.rows && r + x < 0) {
                        uchar pixelValue = img.ptr<uchar>(r + x)[c + y];
                        std::cout << pixelValue + 1 << std::endl;
                        frame.push_back(pixelValue);
                    }
                }
            }
            // Calculate median.
            //std::sort(begin(frame), end(frame));
            img.ptr<uchar>(r)[c] = frame[frame.size() - 1];
        }
    }

}