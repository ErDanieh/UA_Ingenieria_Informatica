#include "mnist.h"

#include <fstream>

/// <summary>
/// Swaps between little endian and big endian encodings. Adapted from code found in https://stackoverflow.com/a/52406754.
/// </summary>
/// <param name="val">The value to be swapped.</param>
/// <returns>
/// A value with the endian swapped.
/// </returns>
uint32_t swapEndian(uint32_t val)
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    
    return (val << 16) | (val >> 16);
}

/// <summary>
/// Loads the MNIST dataset. Adapted from code found in https://stackoverflow.com/a/52406754.
/// </summary>
/// <param name="imageFilename">The MNIST file containing the images.</param>
/// <param name="labelFilename">The MNIST file containing the labels.</param>
/// <param name="dataset">The output dataset with the MNIST data loaded.</param>
/// <returns>
/// True if the dataset was loaded successfully.
/// </returns>
bool mnist::loadMnist(const char* imageFilename, const char* labelFilename, std::vector<TSample> &dataset)
{
    // Open files
    std::ifstream imageFile(imageFilename, std::ios::binary);
    std::ifstream labelFile(labelFilename, std::ios::binary);
    
    if(!imageFile.is_open())
    {
        std::cout<<"Could not open image file "<<imageFilename<<std::endl;
        
        return false;
    }
    else if(!labelFile.is_open())
    {
        std::cout<<"Could not open label file "<<labelFilename<<std::endl;
        
        return false;
    }

    // Read the magic and the meta data
    uint32_t magic;
    uint32_t numItems;
    uint32_t numLabels;
    uint32_t rows;
    uint32_t cols;

    imageFile.read(reinterpret_cast<char*>(&magic), 4);
    magic = swapEndian(magic);
    if(magic != 2051)
    {
        std::cout<<"Incorrect image file magic: "<<magic<<std::endl;
        
        return false;
    }

    labelFile.read(reinterpret_cast<char*>(&magic), 4);
    magic = swapEndian(magic);
    if(magic != 2049)
    {
        std::cout<<"Incorrect label file magic: "<<magic<<std::endl;
        
        return false;
    }

    imageFile.read(reinterpret_cast<char*>(&numItems), 4);
    numItems = swapEndian(numItems);
    labelFile.read(reinterpret_cast<char*>(&numLabels), 4);
    numLabels = swapEndian(numLabels);
    if(numItems != numLabels)
    {
        std::cout<<"Image file count "<<numItems<<" should be equal to label count "<<numLabels<<std::endl;
        
        return false;
    }

    imageFile.read(reinterpret_cast<char*>(&rows), 4);
    rows = swapEndian(rows);
    imageFile.read(reinterpret_cast<char*>(&cols), 4);
    cols = swapEndian(cols);

    char label;
    for (int i = 0; i < numItems; i++)
    {
        char* pixels = new char[rows * cols];
        labelFile.read(&label, 1);
        imageFile.read(pixels, rows * cols);
        dataset.push_back(TSample(pixels, rows, cols, label));
    }
    
    return true;
}
