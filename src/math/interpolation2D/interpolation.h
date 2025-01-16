#pragma once
#include <iostream>
#include <map>
#include <algorithm>

class Interpolation2DMinimalVectorSize:  public std::exception 
{public: const char * what() const throw();};

class Interpolation2DOutOfRange:  public std::exception 
{public: const char * what() const throw();};

class Interpolation2DWrongXaxis:  public std::exception 
{public: const char * what() const throw();};

class Interpolation2D
{
    public : 
        Interpolation2D(std::map<double, double> mapped_x_y_);
        virtual ~Interpolation2D(){};
        virtual double evaluate(double x_) = 0;
        std::map<double, double> mapped_x_y;
        std::vector<double> x; 
        std::vector<double> y; 
        double x_min ;
        double x_max ;
        std::vector<double> get_x_values();
        std::vector<double> get_y_values();
};


