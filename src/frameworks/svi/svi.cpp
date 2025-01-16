#include "svi.h"

/** 
* @file svi.h
* @brief This file defines the framework for the SVI models. 
* 
* References :  
* - "Arbitrage-free SVI volatility surface", Gatheral, Jacquier, 2013. 
*/

/** 
 * @class SVIWrongParameterValue
 * @brief Definition of the error when a SVI parameter value is incorrect. 
 * 
 */

/** 
 * @brief Definition of what() virtual std::exception function.
 * @return The explication of the error.
 */
const char * SVIWrongParameterValue::what() const throw(){
    return "There is an error in the SVI input parameters.";
};

/** 
 * @class SSVIWrongParameterValue
 * @brief Definition of the error when a SSVI parameter value is incorrect. 
 * 
 */

/** 
 * @brief Definition of what() virtual std::exception function.
 * @return The explication of the error.
 */
const char * SSVIWrongParameterValue::what() const throw(){
    return "There is an error in the SSVI input parameters.";
};

/** 
 * @struct SSVI
 * @brief The Surface stochastic volatility inspired model (Power-Law parametrization).
 * 
 */

 /**
 * @var double SSVI::rho_
 * @brief The SSVI model's parameter rho. 
 */

 /**
 * @var double SSVI::nu_
 * @brief The SSVI model's parameter nu. 
 */

 /**
 * @var double SSVI::gamma_
 * @brief The SSVI model's parameter gamma_. 
 */

/** 
 * @brief The main constructor
 * @param rho The SSVI model's parameter rho. 
 * @param nu The SSVI model's parameter nu. 
 * @param gamma The SSVI model's parameter gamma_. 
 * @throw SSVIWrongParameterValue
 */
 SSVI::SSVI(double rho, double nu, double gamma): 
    rho_(rho), nu_(nu_), gamma_(gamma) 
{
    if(abs(rho) > 1){throw SSVIWrongParameterValue();}
    if(gamma > 1 or gamma<0){throw SSVIWrongParameterValue();}
    if(nu < 0){throw SSVIWrongParameterValue();}
};

/**
 * @param atm_total_variance the ATM total variance. 
 * @return The power law parametrization function value. 
 */
double SSVI::prmtrzt(double atm_total_variance)
{
    return nu_*pow(atm_total_variance, gamma_);
};

/**
 * @param atm_total_variance the ATM total variance. 
 * @return The first derivative of the power law parametrization function value. 
 */
double SSVI::dprmtrzt(double atm_total_variance)
{
    return (1-gamma_)*prmtrzt(atm_total_variance);
};

/**
 * @param atm_total_variance the ATM total variance. 
 * @return True if no butterlfy arbitrage, false else. 
 */
bool SSVI::butterfly_arbitrage_check(double atm_total_variance)
{
    double prmtrzt_ = prmtrzt(atm_total_variance);
    double cond1 = atm_total_variance*prmtrzt_*(1+abs(rho_));
    double cond2 = cond1*prmtrzt_;
    if (cond1<=4 and cond2<=4){return true;}
    else{return false;}
};

/**
 * @param atm_total_variance the ATM total variance. 
 * @return True if no calendar spread arbitrage, false else. 
 */
bool SSVI::calendar_spread_arbitrage_check(double atm_total_variance)
{
    double prmtrzt_ = prmtrzt(atm_total_variance);
    double dprmtrzt_ = dprmtrzt(atm_total_variance);
    double value = prmtrzt_*(1+sqrt(1-rho_*rho_))/(rho_*rho_);
    if (dprmtrzt_>=0 and dprmtrzt_<=value){return true;}
    else{return false;}
};

/**
 * @param atm_total_variance the ATM total variance. 
 * @param k The log moneyness.
 * @return The total variance at a specific ATM total viance and log moneyness values. 
 */
double SSVI::total_variance(double k, double atm_total_variance)
{
    double prmtrzt_ = prmtrzt(atm_total_variance);
    double term1 = prmtrzt_*k+rho_;
    double term2 = sqrt(term1*term1 + (1-rho_*rho_));
    return .5*atm_total_variance*(1+rho_*k*prmtrzt_+term2);
};

/**
 * @param atm_total_variance the ATM total variance. 
 * @param k The log moneyness.
 * @param t The year fraction.
 * @return The implied variance at a specific ATM total viance and log moneyness values. 
 */
double SSVI::implied_variance(double k, double atm_total_variance, double t)
{
    return total_variance(k,atm_total_variance)/t;
};

/**
 * @param atm_total_variance the ATM total variance. 
 * @param k The log moneyness.
 * @param t The year fraction.
 * @return The implied volatility at a specific ATM total viance and log moneyness values. 
 */
double SSVI::implied_volatility(double k, double atm_total_variance, double t)
{
    return sqrt(implied_variance(k,atm_total_variance,t));
};

/** 
 * @struct SVI
 * @brief The stochastic volatility inspired model (Jump-wings parametrization).
 */

 /**
 * @var double SVI::vt_
 * @brief The Jump-Wings SVI model's parameter vt. 
 */

 /**
 * @var double SVI::ut_
 * @brief The Jump-Wings SVI model's parameter ut. 
 */

 /**
 * @var double SVI::ct_
 * @brief The Jump-Wings SVI model's parameter ct. 
 */

 /**
 * @var double SVI::pt_
 * @brief The Jump-Wings SVI model's parameter pt. 
 */

 /**
 * @var double SVI::vmt_
 * @brief The Jump-Wings SVI model's parameter vmt. 
 */

 /**
 * @var double SVI::t
 * @brief The Jump-Wings SVI model's parameter t. 
 */

 /**
 * @var double SVI::a
 * @brief The raw SVI model's parameter a. 
 */

 /**
 * @var double SVI::b
 * @brief The raw SVI model's parameter b. 
 */

 /**
 * @var double SVI::m
 * @brief The raw SVI model's parameter m. 
 */

 /**
 * @var double SVI::s
 * @brief The raw SVI model's parameter s. 
 */

 /**
 * @var double SVI::p
 * @brief The raw SVI model's parameter p. 
 */

 /**
 * @var double SVI::beta
 * @brief The parameter beta used for translation from JW-SVI to raw SVI.
 */

 /**
 * @var double SVI::alpha
 * @brief The parameter alpha used for translation from JW-SVI to raw SVI.
 */

  /**
 * @var double SVI::dbdt
 * @brief The first derivative of parameter b in terms of JWSVI parameters with respect to t. 
 */

  /**
 * @var double SVI::dadt
 * @brief The first derivative of parameter a in terms of JWSVI parameters with respect to t. 
 */

  /**
 * @var double SVI::dsdt
 * @brief The first derivative of parameter s in terms of JWSVI parameters with respect to t. 
 */

   /**
 * @var double SVI::dmdt
 * @brief The first derivative of parameter m in terms of JWSVI parameters with respect to t. 
 */

/** 
 * @brief The main constructor
 * @param vt The Jump-Wing SVI model's parameter vt. 
 * @param ut The Jump-Wing SVI model's parameter ut. 
 * @param ct The Jump-Wing SVI model's parameter ct. 
 * @param pt The Jump-Wing SVI model's parameter pt. 
 * @param vmt The Jump-Wing SVI model's parameter vmt. 
 * @param t The Jump-Wing SVI model's parameter t. 
 * @throw SVIWrongParameterValue
 */
 SVI::SVI(double vt, double ut, double ct, double pt, double vmt, double t): 
    vt_(vt), ut_(ut), ct_(ct), pt_(pt), vmt_(vmt), T_(t),
    b(get_b()), p(get_p()),beta(get_beta()), alpha(get_alpha()), 
    m(get_m()), a(get_a()), s(get_s()), dbdt(get_dbdt()), 
    dmdt(get_dmdt()), dsdt(get_dsdt()), dadt(get_dadt())
{
    if(vt_<=0){throw SVIWrongParameterValue();}
    if(vmt_<=0){throw SVIWrongParameterValue();}
    if(T_<=0){throw SVIWrongParameterValue();}
    if(s<=0){throw SVIWrongParameterValue();}
    if((a+b*s*sqrt(1-p*p))<0){throw SVIWrongParameterValue();}
};

/**
 * @return Return the raw SVI parameter b.
 * @throw SVIWrongParameterValue
 */
double SVI::get_b()
{
    double b_ = sqrt(vt_*T_)*(ct_+pt_)/2;
    if (b_<0){throw SVIWrongParameterValue();}
    return b_;
};

/**
 * @return Return the raw SVI parameter p.
 * @throw SVIWrongParameterValue
 */
double SVI::get_p()
{
    double p_;
    if (b==0){p_ = 0.0;}
    else{p_ = 1 - pt_*sqrt(vt_*T_)/b;}
    if (abs(p_)>1.0){throw SVIWrongParameterValue();}
    return p_;
};

/**
 * @return Return the parameter beta used for translation from JW-SVI to raw SVI.
 * @throw SVIWrongParameterValue
 */
double SVI::get_beta()
{
    if (b==0){return 1.0;}
    else
    {
        double beta_ = p - 2*ut_*sqrt(vt_*T_)/b;
        if (abs(beta_)>1.0){throw SVIWrongParameterValue();}
        return beta_;
    }
};

/**
 * @return Return the parameter alpha used for translation from JW-SVI to raw SVI.
 */
double SVI::get_alpha()
{
    if(beta<0){return -sqrt(1/(beta*beta) - 1);}
    if(beta>0){return sqrt(1/(beta*beta) - 1);}
    return 0;
};

/**
 * @return Return the raw SVI parameter m.
 * @throw SVIWrongParameterValue
 */
double SVI::get_m()
{
    if (b==0){return 0.0;}
    else{
        double intterm;
        if (alpha<0){intterm = -sqrt(1+alpha*alpha);}
        else{intterm = sqrt(1+alpha*alpha);}
        return (T_*(vmt_-vt_)/(b*(-p+intterm-alpha*sqrt(1-p*p))));
    }
};

/**
 * @return Return the raw SVI parameter a.
 * @throw SVIWrongParameterValue
 */
double SVI::get_a()
{
    if(m==0){
        return T_*(vmt_+vt_*sqrt(1-p*p))/(1-sqrt(1-p*p));
    }
    else{
        double s_ = alpha*m;
        return T_*vmt_-b*s_*sqrt(1-p*p);
    }
};

/**
 * @return Return the raw SVI parameter s.
 * @throw SVIWrongParameterValue
 */
double SVI::get_s()
{
    if(m==0){
        if (b==0){return 1.0;}
        else{return (vt_*T_ - a)/b;}
    }
    else{return alpha*m;}
};

/**
 * @return True if no butterlfy arbitrage, false else. 
 */
bool SVI::butterfly_arbitrage_check()
{
    double cond1 = sqrt(vt_*T_)*std::max(ct_,pt_);
    double cond2 = (ct_+pt_)*std::max(ct_,pt_);
    if (cond1<2 and cond2 <=2){return true;}
    else{return false;}
};

/**
 * @param k The log moneyness.
 * @return The total variance for a specific log moneyness value. 
 */
double SVI::total_variance(double k)
{
    return a + b*(p*(k-m)+sqrt((k-m)*(k-m)+s*s));
};

/**
 * @param k The log moneyness.
 * @return The implied variance for a specific log moneyness value. 
 */
double SVI::implied_variance(double k)
{
    return total_variance(k)/T_;
};

/**
 * @param k The log moneyness.
 * @return The implied volatility for a specific log moneyness value. 
 */
double SVI::implied_volatility(double k)
{
    return sqrt(implied_variance(k));
};

/**
 * @param k The log moneyness.
 * @return The first derivative of the total variance with respect to k. 
 */
double SVI::dwdk(double k)
{
    double km = k-m;
    return b*(p+km/(sqrt(km*km + s*s)));
};

/**
 * @param k The log moneyness.
 * @return The second derivative of the total variance with respect to k. 
 */
double SVI::dw2dk2(double k)
{
    return sqrt(implied_variance(k));
};

/**
 * @return The first derivative of parameter b in terms of JWSVI parameters with respect to t. 
 */
double SVI::get_dbdt()
{
    return vt_*(ct_+pt_)/(4*sqrt(T_));
};

/**
 * @return The first derivative of parameter m in terms of JWSVI parameters with respect to t. 
 */
double SVI::get_dmdt()
{
    if (b==0){return 0.0;}
    else{
        double factor;
        if (alpha<0){
            double factor = (-p - sqrt(1+alpha*alpha) - alpha*sqrt(1-p*p));
        }
        else{
            double factor = (-p + sqrt(1+alpha*alpha) - alpha*sqrt(1-p*p));
        }
        return (vt_-vmt_)*(b-T_*dbdt)/(factor*b*b);
    }
};

/**
 * @return The first derivative of parameter s in terms of JWSVI parameters with respect to t. 
 */
double SVI::get_dsdt()
{
    if (m==0){
        if (b==0){return 0;}
        else{
            return (b*(vt_-a/T_)+dbdt*(vt_*T_-a))/(b*b);
        }
    }
    else{return alpha*dmdt;}
};

/**
 * @return The first derivative of parameter a in terms of JWSVI parameters with respect to t. 
 */
double SVI::get_dadt()
{
    if (m==0){return a/T_;}
    else{return vmt_-sqrt(1-p*p)*(dbdt*s+dsdt*b);}
};

/**
 * @param k The log moneyness.
 * @return Smile part of the total variance SVI function. 
 */
double SVI::g(double k)
{
    return p*(k-m)+sqrt((k-m)*(k-m)+s*s);
};

/**
 * @param k The log moneyness.
 * @return First derivative of the smile part of the total variance SVI function with respect to t. 
 */
double SVI::dgdt(double k)
{
    return -p*dmdt + (dsdt*s-dmdt*(k-m))/sqrt((k-m)*(k-m) + s*s); 
};

/**
 * @param k The log moneyness.
 * @return First derivative the total variance function. 
 */
double SVI::dwdt(double k)
{
    return dadt + b*dgdt(k) + dbdt*g(k);
};

/**
 * @param k The log moneyness.
 * @return First derivative the total variance function. 
 */
double SVI::risk_neutral_density(double k)
{
    double dwdk_ = dwdk(k);
    double w = total_variance(k);
    double term1 = (1-k*dwdk_/(2*w));
    double term2 = .25*dwdk_*dwdk_*(.25+1/w);
    return term1*term1 - term2 + .5*dw2dk2(k);
};

/**
 * @param k The log moneyness.
 * @return Local variance function. 
 */
double SVI::local_variance(double k)
{
    return dwdt(k)/risk_neutral_density(k);
};

/**
 * @param k The log moneyness.
 * @return Local volatility function. 
 */
double SVI::local_volatility(double k)
{
    return sqrt(local_variance(k)); 
};

/**
 * @return The corresponding powerr law SSVI.
 */
SSVI SVI::get_power_law_ssvi()
{
    double rho_ = 1/(1+pt_/ut_);
    return SSVI(rho_, 2*ut_/rho_, .5);
};


/**
 * @param atm_total_variance the ATM total variance. 
 * @param t The year fraction.
 * @return The SVI model 
 */
SVI SSVI::get_svi(double atm_total_variance, double t)
{
    double f = prmtrzt(atm_total_variance)*sqrt(atm_total_variance);
    return SVI(
        atm_total_variance/t, 
        .5*rho_*f,
        .5*(1+rho_)*f, 
        .5*(1-rho_)*f, 
        atm_total_variance*(1-rho_*rho_)/t, 
        t);
};

