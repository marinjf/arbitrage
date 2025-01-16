#include "array.h"

/** 
* @file array.h
* @brief This file defines an array structure used to store numerical values. 
*/

/** 
* @struct Array
* @brief Definition of an Array to store a vector of numerical values.
*/
/**
 * @var std::vector<double> Array::array_
 * @brief the input vector stored in the array. 
 */

Array::Array(const std::vector<double> array): array_(array){}; 
Array::~Array(){};

/**
 * @brief Calculates the array's mean. . 
 * @return The array's mean. 
 */
double Array::mean()
{
    return std::accumulate(array_.begin(), array_.end(), 0.0)/array_.size();
};

/**
 * @brief Calculates the array's sample variance. 
 * @return The array's sample variance. 
 */
double Array::sample_variance()
{
    double m = mean();
    double accum = 0.0;
    std::for_each (std::begin(array_), std::end(array_), [&](const double d) 
    {
    accum += (d - m) * (d - m);
    });
    return accum / (array_.size()-1);
};

/**
 * @brief Calculates the array's standard deviation. 
 * @return The array's standard deviation. 
 */
double Array::standard_deviation()
{
    return sqrt(sample_variance());
};