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
	cv::Mat tempImage;

	img.copyTo(tempImage);

	int imageChannels = img.channels();

	std::vector<vector> values(imageChannels);

	int halfSize{ kernelSize / 2 };

	int pos = { kernelSize * kernelSize / 2 };

	for (int i{ halfSize }; i < tempImage.rows - halfSize; i++)
	{
		for (int j{ halfSize }; j < tempImage.cols - halfSize; j++)
		{
			for (int channel = 0; channel < imageChannels; channel++)
			{
				values[channel].clear();
			}

			for (int x = { -halfSize }; x <= halfSize; x++)
			{
				for (int y = { -halfSize }; y <= halfSize; y++)
				{
					for (int channel = 0; channel < imageChannels; channel++)
					{
						unsigned char* pixelValuePtr = tempImage.ptr(i + x) + ((j + y) * imageChannels) + channel;

						values[channel].push_back(*pixelValuePtr);
					}
				}
			}

			for (int channel = 0; channel < imageChannels; channel++)
			{
				sort(begin(values[channel]), end(values[channel]));

				unsigned char* pixelValuePtr = image.ptr(i) + (j * imageChannels) + channel;

				*pixelValuePtr = values[channel][pos];
			}
		}
	}
}