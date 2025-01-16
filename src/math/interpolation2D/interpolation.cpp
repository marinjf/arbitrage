#include "interpolation.h"

/** 
* @file interpolation.h
* @brief This file defines the base class for any 2-dimension interpolator. 
*/

/** 
 * @class Interpolation2DMinimalVectorSize
 * @brief Definition of the error when a when the minimal size of the vector 
 * to interpolate is not respected. 
 * 
 */

/** 
 * @brief Definition of what() virtual std::exception function.
 * @return The explication of the error.
 */
const char * Interpolation2DMinimalVectorSize::what() const throw(){
    return "The vector to interpolate must have a size stricly superior than 2.";
};

/** 
 * @class Interpolation2DOutOfRange
 * @brief Definition of the error when trying to interpolate values out of range. 
 * 
 */

/** 
 * @brief Definition of what() virtual std::exception function.
 * @return The explication of the error.
 */
const char * Interpolation2DOutOfRange::what() const throw(){
    return "A value out of the interpolation range cannot be interpolated.";
};

/** 
 * @class Interpolation2DWrongXaxis
 * @brief Definition of the error when the x-axis used for interpolation is not correct. 
 * 
 */

/** 
 * @brief Definition of what() virtual std::exception function.
 * @return The explication of the error.
 */
const char * Interpolation2DWrongXaxis::what() const throw(){
    return "The x-axis must be an increasing vector.";
};

/** 
* @class Interpolation2D
* @brief Definition of the 2-dimension interpolation base class.  
*/

/**
 * @var double Interpolation2D::mapped_x_y
 * @brief The map representing the coordinates to interpolate from.
 */

/**
 * @var double Interpolation2D::x
 * @brief The independant values (x-axis).
 */

/**
 * @var double Interpolation2D::y
 * @brief The dependant values (y-axis). 
 */

/**
 * @var double Interpolation2D::x_min
 * @brief The lower bound from which a value can be interpolated.
 */

/**
 * @var double Interpolation2D::x_max
 * @brief The upper bound from which a value can be interpolated.
 */

/** 
 * @brief The main constructor
 * @param mapped_x_y_ The map representing the coordinates to interpolate from. 
 * @throw Interpolation2DMinimalVectorSize
 * @throw Interpolation2DWrongXaxis
 */
Interpolation2D::Interpolation2D(std::map<double, double> mapped_x_y_): 
    mapped_x_y(mapped_x_y_), x(get_x_values()), x_max(*std::max_element(x.begin(), x.end())), 
    y(*std::min_element(x.begin(), x.end())){};

/**
 * @return The x-axis.
 */
std::vector<double> Interpolation2D::get_x_values()
{
    std::vector<double> keys;
    int i = 0;
    for(auto const& imap: mapped_x_y)
        keys.push_back(imap.first);
        if (i>0){
            if (keys[i-1]>keys[i]){throw Interpolation2DWrongXaxis();}
        }
        i++;
        
        
    if (keys.size()<2){throw Interpolation2DMinimalVectorSize();}
    return keys;
};

/**
 * @return The y-axis.
 */
std::vector<double> Interpolation2D::get_y_values()
{
    std::vector<double> keys;
    for(auto const& imap: mapped_x_y)
        keys.push_back(imap.second);
    return keys;
};
