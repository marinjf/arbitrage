#include "blackscholes.h"

/** 
* @file blackscholes.h
* @brief This file defines the framework for the Black Scholes model. 
* 
* References :  
* - "The Pricing of Options and Corporate Liabilities", Black, Scholes, 1972. 
* - "The pricing of commodity contracts", Black, 1876
*/

/** 
 * @class BlackScholesNonPositiveYearFraction
 * @brief Definition of the mismatch error when the year fraction is not positive. 
 * 
 */

/** 
 * @brief Definition of what() virtual std::exception function.
 * @return The explication of the error.
 */
const char * BlackScholesNonPositiveYearFraction::what() const throw(){
    return "The year fraction cannot be negative or equal to zero.";
};

/** 
 * @class BlackScholesNonPositiveImpliedVolatility
 * @brief Definition of the mismatch error when the implied volatility is not positive. 
 * 
 */
/** 
 * @brief Definition of what() virtual std::exception function.
 * @return The explication of the error.
 */
const char * BlackScholesNonPositiveImpliedVolatility::what() const throw(){
    return "The implied volatility cannot be negative or equal to zero.";
};

/** 
 * @struct BlackScholesClosedForm
 * @brief Used to calculate the Black Scholes analytical formula for euopean vanilla options.
 * 
 */

 /**
 * @var double BlackScholesClosedForm::S_
 * @brief The spot/future price of the underlying.
 */

 /**
 * @var double BlackScholesClosedForm::K_
 * @brief The strike price of the option. 
 */

 /**
 * @var double BlackScholesClosedForm::r_
 * @brief The interest rate.
 */

/**
 * @var double BlackScholesClosedForm::q_
 * @brief The carry cost rate. 
 */

/**
 * @var double BlackScholesClosedForm::sigma_
 * @brief The implied volatility 
 */

/**
 * @var double BlackScholesClosedForm::T_
 * @brief The year fraction. 
 */

/**
 * @var double BlackScholesClosedForm::call_put_flag
 * @brief 1 if the option is a call, -1 if it is a put. 
 */

/**
 * @var double BlackScholesClosedForm::future_flag
 * @brief 0 if the underyling is a future, 1 if not. 
 */

/**
 * @var double BlackScholesClosedForm::mu
 * @brief The underlying drift. 
 */

/**
 * @var double BlackScholesClosedForm::df
 * @brief The discount factor value.
 */

/**
 * @var double BlackScholesClosedForm::d1
 * @brief The d1 values, with respect of the Black scholes formula. 
 */
/**
 * @var double BlackScholesClosedForm::d2
 * @brief The d2 values, with respect of the Black scholes formula. 
 */

/**
 * @var double BlackScholesClosedForm::nd2
 * @brief The standard normal pdf value of d2.
 */

/**
 * @var double BlackScholesClosedForm::nd1
 * @brief The standard normal pdf value of d1.
 */

/**
 * @var double BlackScholesClosedForm::Nd2
 * @brief The standard normal cdf value of d2.
 */

/**
 * @var double BlackScholesClosedForm::Nd1
 * @brief The standard normal cdf value of d1.
 */

 /** 
 * @brief The main constructor
 * @param S The spot/future price of the underlying.
 * @param K The strike price of the option. 
 * @param r The interest rate.
 * @param q The carry cost rate. 
 * @param sigma The implied volatility.
 * @param T The year fraction. 
 * @param is_call indicator if the option is a call (True) or a put (False).
 * @param is_future indicator if the underyling is a future (True) or not (False).
 * @throw BlackScholesNonPositiveImpliedVolatility
 * @throw BlackScholesNonPositiveYearFraction
 */
 BlackScholesClosedForm::BlackScholesClosedForm(
    double S, double K, double r, double q, 
    double sigma, double T, bool is_call, bool is_future): 
    S_(S), K_(K), r_(r), q_(q), sigma_(sigma), T_(T),
    future_flag(set_future_flag(is_future)),
    call_put_flag(set_call_put_flag(is_call)), 
    mu(compute_mu()), df(compute_df()),F(compute_F()), 
    d1(compute_d1()), d2(compute_d2()), nd1(compute_nd1()),
    nd2(compute_nd2()), Nd1(compute_Nd1()), Nd2(compute_Nd2())
{
    if (sigma_<=0){throw BlackScholesNonPositiveImpliedVolatility();}
    if (T_<=0){throw BlackScholesNonPositiveYearFraction();}
};

/**
 * @param is_future the future indicator. 
 * @return return the future flag. 
 */
int BlackScholesClosedForm::set_future_flag(bool is_future)
{
    if (is_future){return 0;}
    else{return 1;}
};

/**
 * @param is_call the call/put indicator. 
 * @return return the call/put flag. 
 */
int BlackScholesClosedForm::set_call_put_flag(bool is_call)
{
    if (is_call){return 1;}
    else{return -1;}
};

/**
 * @return return the discount factor
 */
double BlackScholesClosedForm::compute_df()
{
    return exp(-r_*T_);
};

/**
 * @return return the underlying's drift.
 */
double BlackScholesClosedForm::compute_mu()
{
    return future_flag*(r_-q_);
};

/**
 * @return return the corresponding future price.
 */
double BlackScholesClosedForm::compute_F()
{
    return S_*exp(mu*T_);
};

/**
 * @return return the d1 value.
 */
double BlackScholesClosedForm::compute_d1()
{
    return (log(F/K_) + T_*.5*sigma_*sigma_)/(sigma_*sqrt(T_));
};

/**
 * @return return the d2 value.
 */
double BlackScholesClosedForm::compute_d2()
{
    return d1 - sigma_*sqrt(T_);
};

/**
 * @return return the standard normal pdf of d1.
 */
double BlackScholesClosedForm::compute_nd1()
{
    NormalDistribution stdnorm = NormalDistribution();
    return stdnorm.pdf(d1);
};

/**
 * @return return the standard normal pdf of d2.
 */
double BlackScholesClosedForm::compute_nd2()
{
    NormalDistribution stdnorm = NormalDistribution();
    return stdnorm.pdf(d2);
};

/**
 * @return return the standard normal cdf of d1.
 */
double BlackScholesClosedForm::compute_Nd1()
{
    NormalDistribution stdnorm = NormalDistribution();
    return stdnorm.cdf(call_put_flag*d1);
};

/**
 * @return return the standard normal cdf of d2.
 */
double BlackScholesClosedForm::compute_Nd2()
{
    NormalDistribution stdnorm = NormalDistribution();
    return stdnorm.cdf(call_put_flag*d2);
};

/**
 * @return compute the european vanilla option's price.
 */
double BlackScholesClosedForm::price()
{
    return df*call_put_flag*(F*Nd1 - K_*Nd2);
};

/**
 * @return compute the european vanilla option's delta.
 */
double BlackScholesClosedForm::delta()
{
    return df*call_put_flag*exp(mu*T_)*Nd1;
};

/**
 * @return compute the european vanilla option's gamma.
 */
double BlackScholesClosedForm::gamma()
{
    double drift = exp(mu*T_);
    return df*drift*drift*nd1/(F*sigma_*sqrt(T_));
};

/**
 * @return compute the european vanilla option's theta.
 */
double BlackScholesClosedForm::theta()
{
    double term1 = -F*df*nd1*sigma_/(2*sqrt(T_));
    double term2 = -call_put_flag*r_*K_*df*Nd2; 
    double term3 = call_put_flag*(r_-mu)*F*df*Nd1;
    return term1+term2+term3;
};

/**
 * @return compute the european vanilla option's vega.
 */
double BlackScholesClosedForm::vega()
{
    return F*df*nd1*sqrt(T_);
};

/**
 * @return compute the european vanilla option's rho.
 */
double BlackScholesClosedForm::rho()
{
    if (future_flag == 0){
        return -T_*df*price();
    }
    else{
        return call_put_flag*K_*T_*Nd2*df;
    };
};

/**
 * @return compute the european vanilla option's epsilon.
 */
double BlackScholesClosedForm::epsilon()
{
    if (future_flag == 0){
        return 0.0;
    }
    else{
        return -call_put_flag*F*T_*Nd1*df;
    };
};

/**
 * @return compute the european vanilla option's vanna.
 */
double BlackScholesClosedForm::vanna()
{
    return -df*exp(mu*T_)*nd1*d2/sigma_;
};

/**
 * @return compute the european vanilla option's volga.
 */
double BlackScholesClosedForm::volga()
{
    return vega()*d1*d2/sigma_;
};

/**
 * @return compute the european vanilla option's charm.
 */
double BlackScholesClosedForm::charm()
{
    double drift = exp(mu*T_);
    double term1 = (mu-r_)*df*drift*Nd1; 
    double term2 = (2*mu*T_ - sigma_*d2*sqrt(T_))/(2*T_*sigma_*sqrt(T_));
    double term3 = df*drift*nd1; 
    return call_put_flag*term1 - term2*term3;
};

/**
 * @return compute the european vanilla option's veta.
 */
double BlackScholesClosedForm::veta()
{
    double term1 = -F*df*nd1*sqrt(T_);
    double term2 = (r_-mu)+mu*d1/(sigma_*sqrt(T_));
    double term3 = (1+d1*d2)/(2*T_); 
    return term1*(term2-term3);
};

/**
 * @return compute the european vanilla option's speed.
 */
double BlackScholesClosedForm::speed()
{
    double term1 = -exp(mu*T_)*gamma()*(1+d1/(sigma_*sqrt(T_)));
    return term1/F;
};

/**
 * @return compute the european vanilla option's zomma.
 */
double BlackScholesClosedForm::zomma()
{
    return gamma()*(d1*d2-1)/sigma_;
};

/**
 * @return compute the european vanilla option's ultima.
 */
double BlackScholesClosedForm::ultima()
{
    return -vega()*(d1*d2*(1-d1*d2) + d1*d1 + d2*d2)/(sigma_*sigma_);
};

/**
 * @return compute the european vanilla option's color.
 */
double BlackScholesClosedForm::color()
{
    double term1 = d1*(2*mu*T_ - d2*sigma_*sqrt(T_))/(sigma_*sqrt(T_));
    return gamma()*(2*(r_-mu) + 1 + term1)/(2*T_);
};

/**
 * @return compute the european vanilla option's dual delta.
 */
double BlackScholesClosedForm::dual_delta()
{
    return -call_put_flag*df*Nd2;
};

/**
 * @return compute the european vanilla option's dual gamma.
 */
double BlackScholesClosedForm::dual_gamma()
{
    return df*nd2/(K_*sigma_*sqrt(T_));
};



