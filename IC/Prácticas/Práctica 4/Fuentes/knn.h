#ifndef __KNN_H
#define __KNN_H

#include "sample.h"

#include <vector>

namespace knn
{
    /// <summary>
    /// K-Nearest Neighbors classifier implementation.
    /// </summary>
    class KNN
    {
        public:
            /// <summary>
            /// Creates a new instance of the KNN classifier.
            /// </summary>
            /// <param name="train">The training samples.</param>
            /// <param name="k">The k neighbors to compute the classification.</param>
            KNN(const std::vector<TSample> &train, int k=1)
            {
            	for(int i=0;i<train.size();i++)
            		this->train.push_back(train[i]);
            		
            	this->k = k;
            };
            
            /// <summary>
            /// Classifies the specified sample.
            /// </summary>
            /// <param name="test">The test sample to be classified.</param>
            /// <returns>
            /// An integer that represents the most common label of the k nearest neighbors of the test samples.
            /// </returns>
            int classify(const TSample &test) const;
            
            /// <summary>
            /// Classifies and evaluates performance with the specified samples.
            /// </summary>
            /// <param name="test">The test samples to be classified.</param>
            /// <param name="labels">Output paramter with a vector of integers that represents the most common label of the k nearest neighbors for each of the test samples.</param>
            /// <returns>
            /// The accuracy of the classification.
            /// </returns>
            double classifyAndEvaluate(const std::vector<TSample> &test, std::vector<int> &labels) const;
            
        private:
            /// <summary>
            /// The training data samples.
            /// </summary>
            std::vector<TSample> train;
            
            /// <summary>
            /// The k parameter.
            /// </summary>
            int k;
    };
}

#endif
