#pragma once 
#include <iostream>
#include <numbers>
#include <cmath>
#include <random>
#include "../../../math/probability/probability.h"
#include "../../../math/numbers.h"

class NormalDistributionNonPositiveSigma: public std::exception 
{public: const char * what() const throw();};

struct NormalDistribution: ProbabilityDistribution
{
    double mu_; 
    double sigma_;
    NormalDistribution(); 
    NormalDistribution(double mu, double sigma); 
    ~NormalDistribution(){};
    double pdf(double x); 
    double cdf(double x); 
    double random();
};
