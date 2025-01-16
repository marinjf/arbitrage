#pragma once 
#include <iostream>
#include "../../math/probability/normal/normal.h"

class BlackScholesNonPositiveImpliedVolatility:  public std::exception 
{public: const char * what() const throw();};

class BlackScholesNonPositiveYearFraction:  public std::exception 
{public: const char * what() const throw();};

struct BlackScholesClosedForm
{
    double S_; 
    double K_; 
    double r_; 
    double q_; 
    double sigma_; 
    double T_; 
    int call_put_flag; 
    int future_flag; 
    double mu; 
    double F; 
    double df; 
    double d1; 
    double d2; 
    double Nd1; 
    double Nd2; 
    double nd1; 
    double nd2; 
    BlackScholesClosedForm(
        double S, 
        double K, 
        double r, 
        double q, 
        double sigma, 
        double T, 
        bool is_call, 
        bool is_future
    );
    ~BlackScholesClosedForm(){}; 
    int set_future_flag(bool is_future); 
    int set_call_put_flag(bool is_call); 
    double compute_df(); 
    double compute_mu();
    double compute_F(); 
    double compute_d1(); 
    double compute_d2(); 
    double compute_nd1(); 
    double compute_nd2(); 
    double compute_Nd1(); 
    double compute_Nd2(); 
    double price();
    double delta();
    double gamma();
    double theta();
    double vega();
    double rho();
    double epsilon();
    double vanna();
    double volga();
    double charm();
    double veta();
    double zomma();
    double speed();
    double color();
    double ultima();
    double dual_delta();
    double dual_gamma();
}; 