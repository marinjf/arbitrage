#pragma once
#include <iostream>
#include <map>
#include "../../../math/interpolation2D/interpolation.h"

class LinearInterpolation2D: public Interpolation2D
{
    public :
        LinearInterpolation2D(std::map<double, double> mapped_x_y_);
        ~LinearInterpolation2D(){};
        double linear_interpolate(double x0, double y0, double x1, double y1, double x);
        double evaluate(double x_) override; 

};