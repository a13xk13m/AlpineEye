#include <opencv2/core/mat.hpp>
#include "ImageProcessing.h"
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>

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

void ImageProc::eucConnect(cv::Mat& img) {
    int coords[2] = { 0, 0 };
    std::vector<std::vector<int>> endpoints;
    for (int r = 0; r < img.rows; r++) {
        for (int c = 0; c < img.cols; c++) {
            std::vector<int> tempCoords = { 0, 0 };
            // Check if pixel is connected on at least two sides to another 
            // white pixel.
            int neighbors = 0;
            int visited = 0;

            uchar currPixel = img.ptr<uchar>(r)[c];
            if (currPixel == 255) {
                for (int x = { -1 }; x <= 1; x++)
                {
                    for (int y = { -1 }; y <= 1; y++)
                    {
                        if (c + x < img.cols && c + x > 0 && r + x < img.rows && r + x > 0) {
                            uchar pixelValue = img.ptr<uchar>(r + x)[c + y];
                            if (pixelValue == 255) {
                                neighbors++;
                            }
                            visited++;
                        }
                    }
                }
                // Add coordinates of endpoint to vector.
                if (neighbors < 2 && visited == 9) {
                    tempCoords[0] = r;
                    tempCoords[1] = c;
                    endpoints.emplace_back(tempCoords);
                }
            }
        }
    }
    std::cout << endpoints.size() << std::endl;
}