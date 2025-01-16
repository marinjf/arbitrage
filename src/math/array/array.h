#pragma once 
#include <iostream>
#include <vector>
#include <numeric>
#include <any>

struct Array
{
    std::vector<double> array_;
    Array(const std::vector<double> array); 
    ~Array();
    double mean(); 
    double sample_variance();
    double standard_deviation(); 
};