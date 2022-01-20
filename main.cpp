#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "ImageProcessing.h"
using namespace cv;

int main()
{
    std::string image_path = samples::findFile("Mt_Washington1.png");
    Mat img = ImageProc::openImage(image_path);
    img = ImageProc::crop(img, 4500, 2000, 2000, 2000);
    //img = ImageProc::stripChannel(img, 'r');
    // Orange for topo lines are r: 166, g: 116, b: 66
    img = ImageProc::boostColor(img, 66, 116, 166, 40);
    img = ImageProc::inverse(img);
    imshow("Before", img);
    cv::Mat img2 = ImageProc::denoise(img, 0.25, 2);
    imshow("After", img2);
    int k = waitKey(0); 
    return 0;
}