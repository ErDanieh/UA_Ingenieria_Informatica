#ifndef __MNIST_H__
#define __MNIST_H__

#include "sample.h"

#include <cstring>
#include <vector>

namespace mnist
{
    /// <summary>
    /// Loads the MNIST dataset.
    /// </summary>
    /// <param name="imageFilename">The MNIST file containing the images.</param>
    /// <param name="labelFilename">The MNIST file containing the labels.</param>
    /// <param name="dataset">The output dataset with the MNIST data loaded.</param>
    /// <returns>
    /// True if the dataset was loaded successfully.
    /// </returns>
    bool loadMnist(const char* imageFilename, const char* labelFilename, std::vector<TSample> &dataset);
}

#endif
