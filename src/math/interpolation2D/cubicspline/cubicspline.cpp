#include "cubicspline.h"

/** 
* @file cubicspline.h
* @brief This file defines the cubic spline interpolation. 
*/

/** 
* @class CubicSpline2D
* @brief Definition of the cubic spline 2D interpolation class.  
*/

/** 
 * @brief The main constructor
 * @param mapped_x_y_ The map representing the coordinates to interpolate from. 
 * @throw InterpolationMinimalVectorSize
 * @throw Interpolation2DWrongXaxis
 */
CubicSpline2D::CubicSpline2D(std::map<double, double> mapped_x_y_): 
    Interpolation2D(mapped_x_y_)
{
    get_parameters();
};

/**
* @brief Set the cubic spline parameters. This methods basically estimate each polynomial's parameters 
* by solving a system of equations from: the spline continuity condition and the boundary conditions. 
 */
void CubicSpline2D::get_parameters()
{
    std::vector<double> x = Interpolation2D::x;
    std::vector<double> y = Interpolation2D::y;
    int n = x.size() - 1;
    x_ = Interpolation2D::x;
    a_ = Interpolation2D::y;

    std::vector<double> h(n), alpha(n);
    for (int i = 0; i < n; ++i) {
        h[i] = x[i + 1] - x[i];
    }

    for (int i = 1; i < n; ++i) {
        alpha[i] = (3.0 / h[i]) * (a_[i + 1] - a_[i]) - (3.0 / h[i - 1]) * (a_[i] - a_[i - 1]);
    }

    std::vector<double> l(n + 1), mu(n), z(n + 1);
    l[0] = 1.0;
    mu[0] = 0.0;
    z[0] = 0.0;

    for (int i = 1; i < n; ++i) {
        l[i] = 2.0 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n] = 1.0;
    z[n] = 0.0;
    c_.resize(n + 1);
    b_.resize(n);
    d_.resize(n);
    c_[n] = 0.0;

    for (int j = n - 1; j >= 0; --j) {
        c_[j] = z[j] - mu[j] * c_[j + 1];
        b_[j] = (a_[j + 1] - a_[j]) / h[j] - h[j] * (c_[j + 1] + 2.0 * c_[j]) / 3.0;
        d_[j] = (c_[j + 1] - c_[j]) / (3.0 * h[j]);
    }
};

/**
 * @param x_ The value to interpolate.
 * @return The cubic spline interpolated value.
 * @throw Interpolation2DOutOfRange
 */
double CubicSpline2D::evaluate(double x_)
{
    if (x_ < Interpolation2D::x_min || x_ > Interpolation2D::x_max){ 
        throw Interpolation2DOutOfRange();}

    if(x_==Interpolation2D::x_max){return Interpolation2D::mapped_x_y.at(x_max);}

    int i = 0;
    for (int j = 1; j < Interpolation2D::x.size(); ++j) {
        if (x_ < Interpolation2D::x[j]) {
            i = j - 1;
            break;
        }
    }
    double dx = x_ - Interpolation2D::x[i];
    return a_[i] + b_[i] * dx + c_[i] * dx * dx + d_[i] * dx * dx * dx;


};