#ifndef __CROSS_VALIDATION_H__
#define __CROSS_VALIDATION_H__

#include "sample.h"

#include <vector>
#include <string>

namespace crossValidation
{
    /// <summary>
    /// Class that performs a Cross Validation.
    /// </summary>
    class CrossValidation
    {
        public:
            /// <summary>
            /// Creates a Cross Validation instance.
            /// </summary>
            /// <param name="dataset">The dataset to be used.</param>
            /// <param name="folds">The number of folds.</param>
            /// <returns>
            /// An instance of a Cross Validation.
            /// </returns>
            CrossValidation(const std::vector<TSample> &dataset, uint folds)
            {
                for(int i=0;i<dataset.size();i++)
                {
                    this->dataset.push_back(dataset[i]);
                }
                this->folds = folds;
            };
            
            /// <summary>
            /// Performs an N-Fold Cross Validation with the specified KNN parameter.
            /// </summary>
            /// <param name="k">The K parameter of the KNN classifier.</param>
            /// <returns>
            /// A value in the range [0.0, 1.0] indicating the averaged accuracy of the KNN in the N folds.
            /// </returns>
            double validate(uint k) const;
            
            /// <summary>
            /// Creates an N-Fold Cross Validation instance.
            /// </summary>
            /// <param name="dataset">The dataset to be used.</param>
            /// <param name="folds">The number of folds.</param>
            /// <returns>
            /// An instance of an N-Fold Cross Validation.
            /// </returns>
            static CrossValidation NFold(const std::vector<TSample> &dataset, uint folds)
            {
                return CrossValidation(dataset, folds);
            };
            
            /// <summary>
            /// Creates a leave-one-out Cross Validation instance.
            /// </summary>
            /// <param name="dataset">The dataset to be used.</param>
            /// <returns>
            /// An instance of a leave-one-out Cross Validation.
            /// </returns>
            static CrossValidation LeaveOneOut(const std::vector<TSample> &dataset)
            {
                return CrossValidation(dataset, dataset.size());
            };
            
            /// <summary>
            /// Gets the name of the Cross Validation, either N-Fold or leave-one-out.
            /// </summary>
            std::string getName() const;
            
        private:
        
            /// <summary>
            /// The whole dataset.
            /// </summary>
            std::vector<TSample> dataset;
            
            /// <summary>
            /// The number of folds for the N-Fold Cross Validation. If N is equal to dataset size, then a leave-one-out cross validation is performed.
            /// </summary>
            uint folds;
            
            /// <summary>
            /// Splits the dataset into train and validation subsets for an N-Fold Cross Validation.
            /// </summary>
            /// <param name="train">The output training data.</param>
            /// <param name="validation">The output validation data.</param>
            /// <param name="fold">The fold to be used as validation data.</param>
            void splitDataset(std::vector<TSample> &train, std::vector<TSample> &validation, uint fold) const;
    };
}

#endif
