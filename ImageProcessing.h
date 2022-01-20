#pragma once
#include <string>
#include <opencv2/core/mat.hpp>

// Contains all of the process that an image undergoes to be cleaned and processed in order 
// to be turned into a model.

namespace ImageProc {
	// Takes an image path and opens it, return a pointer to the image for future processing.
	// Input - Path
	// Output - Image
	cv::Mat openImage(std::string path);

	// Strips a color channel (RGB) from the image. Used to remove green areas, etc.
	// Input - channel, image
	// Channel can be b, g, r
	// Output - Image
	cv::Mat stripChannel(cv::Mat& img, char channel);

	// Converts and image matrix to black and white.
	// ~124 seems to be the sweet spot for the threshold.
	// - Image, threshold for binary conversion.
	// - Image
	cv::Mat toBW(cv::Mat& img, std::size_t threshold);

	// Crops an image.
	// - Image, x, y, width, height
	// - Image
	cv::Mat crop(cv::Mat& img, std::size_t x, std::size_t y, std::size_t width, std::size_t height);

	// Boosts a color and sets others to 0.
	// - Image, blue, green, red, radius of filter band
	// - Image
	cv::Mat boostColor(cv::Mat& img, std::size_t blue, std::size_t green, std::size_t red, std::size_t radius);

	// Inveres an image with cv::bitwise_not
	// - Image
	// - Image
	cv::Mat inverse(cv::Mat& img);
	
	// Denoises a binary image by removing free floating 1s that don't have neighbors.
	// - Image, % of 255 neighbors before a pixels is set to 255, number of passes to denoise.
	// - Image
	cv::Mat denoise(cv::Mat& img, double threshold, std::size_t passes);

	// Processes an image and returns the final, fully processed, version.
	// - Image
	// - Image
	cv::Mat process(cv::Mat& img);
}