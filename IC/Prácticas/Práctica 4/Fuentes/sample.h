#ifndef __SAMPLE_H__
#define __SAMPLE_H__

#include <opencv2/core/types_c.h>
#include <opencv2/opencv.hpp>

/// <summary>
/// Struct that represents a sample.
/// </summary>
typedef struct TSample
{
    /// <summary>
    /// Initializes a new instance of TSample.
    /// </summary>
    /// <param name="pixels">The pixels of the sample as an array of bytes.</param>
    /// <param name="rows">The number of rows of the image.</param>
    /// <param name="cols">The number of columns of the image.</param>
    /// <param name="label">The label of this sample.</param>
    TSample(char* pixels, int rows, int cols, int label);
    
    /// <summary>
    /// An OpenCV Mat representing the sample data.
    /// </summary>
    cv::Mat image;
    
    /// <summary>
    /// The label of this sample.
    /// </summary>
    int label;
    
}TSample;

#endif
