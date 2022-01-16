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
	cv::Mat stripChannel(char channel, cv::Mat& img);

	// Converts and image matrix to black and white.
	// - Image
	// - Image
	cv::Mat toBW(cv::Mat& img, std::size_t threshold);

	// Processes an image and returns the final, fully processed, version.
	// - Image
	// - Image
	cv::Mat process(cv::Mat& img);
}