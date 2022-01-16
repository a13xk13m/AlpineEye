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
    img = ImageProc::toBW(img, 128);
    imshow("Display window", img);
    int k = waitKey(0); 
    return 0;
}