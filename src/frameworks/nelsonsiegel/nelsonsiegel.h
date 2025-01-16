#pragma once 
#include <iostream>

struct NelsonSiegel
{
    double b0_; 
    double b1_;
    double b2_; 
    double tau_; 
    NelsonSiegel(double b0, double b1, double b2, double tau); 
    ~NelsonSiegel(){}; 
    double get_rate(double t);
}; 

struct NelsonSiegelSvensson
{
    double b0_; 
    double b1_;
    double b2_; 
    double b3_; 
    double tau1_; 
    double tau2_; 
    NelsonSiegelSvensson(double b0, double b1, double b2, double b3, double tau1, double tau2); 
    ~NelsonSiegelSvensson(){}; 
    double get_rate(double t);
}; 

