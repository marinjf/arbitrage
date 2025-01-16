#include "linearinterplation.h"

/** 
* @file linearinterplation.h
* @brief This file defines the linear interpolation. 
*/

/** 
* @class LinearInterpolation2D
* @brief Definition of the linear interpolation class.  
*/

/** 
 * @brief The main constructor
 * @param mapped_x_y_ The map representing the coordinates to interpolate from. 
 * @throw InterpolationMinimalVectorSize
 * @throw Interpolation2DWrongXaxis
 */
LinearInterpolation2D::LinearInterpolation2D(std::map<double, double> mapped_x_y_): 
    Interpolation2D(mapped_x_y_){};

/**
 * @param x0 The x-axis value from coordonate 0.
 * @param y0 The y-axis value from coordonate 0.
 * @param x1 The x-axis value from coordonate 1.
 * @param y1 The y-axis value from coordonate 1.
 * @param x The value to interpolate.
 * @return The linear interpolated value.
 */
double LinearInterpolation2D::linear_interpolate(double x0, double y0, double x1, double y1, double x)
{
    return y0 + (x - x0) * (y1 - y0) / (x1 - x0);
};

/**
 * @param x_ The value to interpolate.
 * @return The linear interpolated value.
 * @throw Interpolation2DOutOfRange
 */
double LinearInterpolation2D::evaluate(double x_)
{
    if (x_ < Interpolation2D::x_min || x_ > Interpolation2D::x_max){ 
        throw Interpolation2DOutOfRange();}
    
    for (int i = 1; i < Interpolation2D::x.size(); ++i) {
        if (x_ >= Interpolation2D::x[i-1] && x_ <= Interpolation2D::x[i]) {
            double x0 = Interpolation2D::x[i-1]; 
            double x1 = Interpolation2D::x[i];
            return linear_interpolate(
                x0, Interpolation2D::mapped_x_y.at(x0),
                x1, Interpolation2D::mapped_x_y.at(x1), x_);
        }
    }
};