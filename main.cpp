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
    ImageProc::crop(img, 4500, 3000, 1000, 500);
    // Orange for topo lines are r: 166, g: 116, b: 66
    ImageProc::boostColor(img, 66, 116, 166, 0);
    ImageProc::eucConnect(img);
    imwrite("output.png", img);
    imshow("After", img);
    int k = cv::waitKey(0);
    return 0;
}