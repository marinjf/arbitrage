#pragma once 
#include <iostream>

class SSVIWrongParameterValue:  public std::exception 
{public: const char * what() const throw();};


class SVIWrongParameterValue:  public std::exception 
{public: const char * what() const throw();};

struct SSVI
{
    double rho_; 
    double nu_; 
    double gamma_; 
    SSVI(double rho, double nu, double gamma); 
    ~SSVI(){}; 
    SVI get_svi(double atm_total_variance, double t);
    double prmtrzt(double atm_total_variance); 
    double dprmtrzt(double atm_total_variance); 
    bool butterfly_arbitrage_check(double atm_total_variance); 
    bool calendar_spread_arbitrage_check(double atm_total_variance); 
    double total_variance(double k, double atm_total_variance); 
    double implied_variance(double k, double atm_total_variance, double t); 
    double implied_volatility(double k, double atm_total_variance, double t); 
    double risk_neutral_density(double k, double atm_total_variance, double t); 
    double local_volatility(double k, double atm_total_variance, double t); 
    double atm_volatility_skew(double k, double atm_total_variance, double t);
};

struct SVI
{
    double vt_; 
    double ut_; 
    double ct_;
    double pt_;
    double vmt_; 
    double T_; 
    double a; 
    double beta; 
    double alpha;
    double b; 
    double m; 
    double s; 
    double p; 
    double dmdt; 
    double dadt; 
    double dsdt; 
    double dbdt; 
    SVI(double vt, double ut, double ct, double pt, double vmt, double t); 
    ~SVI(){}; 
    double get_a(); 
    double get_b(); 
    double get_alpha(); 
    double get_beta(); 
    double get_m(); 
    double get_s(); 
    double get_p(); 
    double dwdk(double k);
    double dw2dk2(double k);
    double get_dbdt();
    double get_dsdt();
    double get_dadt();
    double get_dmdt();
    double g(double k);
    double dgdt(double k);
    double dwdt(double k);
    SSVI get_power_law_ssvi();
    bool butterfly_arbitrage_check(); 
    bool calendar_spread_arbitrage_check(SVI svi); 
    double total_variance(double k); 
    double implied_variance(double k); 
    double implied_volatility(double k); 
    double risk_neutral_density(double k); 
    double local_variance(double k); 
    double local_volatility(double k); 
};

struct ReducedSVI
{
    double vt_; 
    double nu_; 
    double rho_; 
    double T_; 
    SVI svi; 
    ReducedSVI(double vt, double nu, double rho, double t); 
    ~ReducedSVI(){}; 
    SVI get_svi();
    bool butterfly_arbitrage_check(); 
    bool calendar_spread_arbitrage_check(ReducedSVI rsvi); 
};
