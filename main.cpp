#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "ImageProcessing.h"
#include <opencv2/imgproc.hpp>

int main()
{
    std::string image_path = cv::samples::findFile("Mt_Washington1.png");
    cv::Mat img = ImageProc::openImage(image_path);
    ImageProc::crop(img, 4500, 2000, 2000, 2000);
    // Orange for topo lines are r: 166, g: 116, b: 66
    //ImageProc::boostColor(img, 66, 116, 166, 40);
    //ImageProc::inverse(img);
    ImageProc::adaptiveThresholding(img, 66, 116, 40, 3);
    imshow("Before", img);
    //ImageProc::denoise(img, 0.25, 2);
    int k = cv::waitKey(0);
    return 0;
}