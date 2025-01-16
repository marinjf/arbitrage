#include "normal.h"

/** 
* @file normal.h
* @brief This file defines the normal probability distributions. 
*/

/** 
 * @class NormalDistributionNonPositiveSigma
 * @brief Definition of negative sigma error for normal ditribution.
 */
/** 
 * @brief Definition of what() virtual std::exception function.
 * @return The explication of the error.
 */
const char * NormalDistributionNonPositiveSigma::what() const throw(){
    return "The parameter sigma for the normal distribution has to be positive.";
};

/** 
* @struct NormalDistribution
* @brief Defition of the normal distribution.
*/
/**
 * @var double NormalDistribution::mu_
 * @brief The expected value parameter.
 */
/**
 * @var double NormalDistribution::sigma_
 * @brief The standard deviation value parameter.
 * @see Future
 */

/** 
* @brief NormalDistribution standard constructor, the expected value is fixed at 0
* and the standard deviation is fixed at 1. 
*/
NormalDistribution::NormalDistribution():mu_(0.0),sigma_(1.0){}; 
/** 
* @brief NormalDistribution constructor
* @param mu The expected value. 
* @param sigma The standard deviation value. 
* @throws NormalDistributionNonPositiveSigma
*/
NormalDistribution::NormalDistribution(double mu, double sigma):mu_(mu),sigma_(sigma)
{
    if (sigma_<=0){throw NormalDistributionNonPositiveSigma();}
}; 

/**
 * @brief Calculates the normal probability density 
 * @param x The value to estimate the pdf with.
 * @return The probability density of the value x.
 */
double NormalDistribution::pdf(double x)
{
    double factor = 1/(sigma_*sqrt(2*numbers::PI));
    double z = (x - mu_)/sigma_;
    return factor*exp(-.5*z*z);
};

/**
 * @brief Calculates the cumlative probability. 
 *
 * Method developed in "Better approximations to cumulative normal functions" from Graeme West (2004).
 *
 * @param x The value to estimate the cdf with.
 * @return The cumlative probability of the value x.
 */
double NormalDistribution::cdf(double x)
{
    static const double RT2PI = sqrt(4.0*acos(0.0));

    static const double SPLIT = 7.07106781186547;

    static const double N0 = 220.206867912376;
    static const double N1 = 221.213596169931;
    static const double N2 = 112.079291497871;
    static const double N3 = 33.912866078383;
    static const double N4 = 6.37396220353165;
    static const double N5 = 0.700383064443688;
    static const double N6 = 3.52624965998911e-02;
    static const double M0 = 440.413735824752;
    static const double M1 = 793.826512519948;
    static const double M2 = 637.333633378831;
    static const double M3 = 296.564248779674;
    static const double M4 = 86.7807322029461;
    static const double M5 = 16.064177579207;
    static const double M6 = 1.75566716318264;
    static const double M7 = 8.83883476483184e-02;

    const double z = fabs((x-mu_)/sigma_);
    double c = 0.0;

    if(z<=37.0)
    {
        const double e = exp(-z*z/2.0);
        if(z<SPLIT)
        {
        const double n = (((((N6*z + N5)*z + N4)*z + N3)*z + N2)*z + N1)*z + N0;
        const double d = ((((((M7*z + M6)*z + M5)*z + M4)*z + M3)*z + M2)*z + M1)*z + M0;
        c = e*n/d;
        }
        else
        {
        const double f = z + 1.0/(z + 2.0/(z + 3.0/(z + 4.0/(z + 13.0/20.0))));
        c = e/(RT2PI*f);
        }
    }
    return x<=0.0 ? c : 1-c;
};

/**
 * @brief Compute a random sample number from the defined normal distribution.
 * @param generator 
 * @return A random number sampled from the normal distribution.
 */
double NormalDistribution::random()
{
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::normal_distribution<double> distribution(mu_,sigma_);
    return distribution(gen);
};


