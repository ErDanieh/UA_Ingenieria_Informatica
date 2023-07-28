#include "sample.h"

/// <summary>
/// Initializes a new instance of TSample.
/// </summary>
/// <param name="pixels">The pixels of the sample as an array of bytes.</param>
/// <param name="rows">The number of rows of the image.</param>
/// <param name="cols">The number of columns of the image.</param>
/// <param name="label">The label of this sample.</param>
TSample::TSample(char* pixels, int rows, int cols, int label)
{
	this->image = cv::Mat(rows, cols, CV_8UC1, pixels);
	cv::resize(this->image, this->image, cv::Size(this->image.rows / 2, this->image.cols / 2), 0, 0, cv::INTER_LINEAR);
	cv::normalize(this->image, this->image, 0.0, 1.0, cv::NORM_MINMAX, CV_32FC1);
	this->label = label;
};
