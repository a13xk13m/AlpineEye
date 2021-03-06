#pragma once
#include <string>
#include <opencv2/core/mat.hpp>

// Contains all of the process that an image undergoes to be cleaned and processed in order 
// to be turned into a model.
// All image processing functions modify the image inplace.

// The below article was used as reference for denoising and other algorithms.
// https://efxa.org/2018/06/25/digital-image-processing-algorithms-implemented-with-c-and-opencv/


namespace ImageProc {
	// Takes an image path and opens it, return a pointer to the image for future processing.
	// Input - Path
	// Output - Image
	cv::Mat openImage(std::string path);

	// Crops an image.
	// - Image, x, y, width, height
	void crop(cv::Mat& img, std::size_t x, std::size_t y, std::size_t width, std::size_t height);

	// Boosts a color and sets others to 0.
	// - Image, blue, green, red, radius of filter band
	void boostColor(cv::Mat& img, std::size_t blue, std::size_t green, std::size_t red, std::size_t radius);

	// Connects lines in an image using closest Euclidian distance.
    // Input - Image
    // Output - Image
	void eucConnect(cv::Mat& img);

	// Processes an image and returns the final, fully processed, version.
	// - Image
	cv::Mat process(cv::Mat& img);
}