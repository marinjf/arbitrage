#pragma once
#include <iostream>
#include <map>
#include "../../../math/interpolation2D/interpolation.h"

class CubicSpline2D: public Interpolation2D
{
    public :
        CubicSpline2D(std::map<double, double> mapped_x_y_);
        double evaluate(double x_) override; 
        void get_parameters();
        ~CubicSpline2D(){};
    private : 
        std::vector<double> x_;
        std::vector<double> a_, b_, c_, d_;

};

