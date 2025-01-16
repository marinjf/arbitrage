#pragma once 
#include <iostream>

struct ProbabilityDistribution
{
    ProbabilityDistribution(); 
    virtual ~ProbabilityDistribution(){};
    virtual double pdf(double x) = 0; 
    virtual double cdf(double x) = 0; 
    virtual double random() = 0;
};


