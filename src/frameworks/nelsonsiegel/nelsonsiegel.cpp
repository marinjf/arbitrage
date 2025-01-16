#include "nelsonsiegel.h"

/** 
* @file nelsonsiegel.h
* @brief This file defines the framework for the "Nelson-Siegel" type models. 
* 
* References :  
* - Parsimlonious modeling of yield curve (Nelson & Siegel, 1987).
* - "Estimating forward interest rates with the extended Nelson & Siegel method" (Svensson, 1994).
*/

/** 
 * @struct NelsonSiegel
 * @brief The Nelson-Siegel model framework.
 * 
 */

 /**
 * @var double NelsonSiegel::b0_
 * @brief Themodel's parameter beta 0. 
 */

 /**
 * @var double NelsonSiegel::b1_
 * @brief The model's parameter beta 1. 
 */

 /**
 * @var double NelsonSiegel::b2_
 * @brief The model's parameter beta 2. 
 */

/**
 * @var double NelsonSiegel::tau_
 * @brief The model's parameter tau. 
 */

/** 
 * @brief The main constructor
 * @param b0 The model's parameter beta 0.
 * @param b1 The model's parameter beta 1.
 * @param b2 The model's parameter beta 2. 
 * @param tau The model's parameter tau. 
 */
 NelsonSiegel::NelsonSiegel(double b0, double b1, double b2, double tau): 
    b0_(b0), b1_(b1), b2_(b2), tau_(tau) {};

/**
 * @param t The year fraction to evaluate the model from.
 * @return The corresponding rate. 
 */
double NelsonSiegel::get_rate(double t)
{
   double tt = t/tau_; 
   return b0_ + b1_*exp(-tt) + b2_*(tt*exp(-tt));
};

/** 
 * @struct NelsonSiegelSvensson
 * @brief The Svensson's extension of the Nelson-Siegel model framework.
 * 
 */

 /**
 * @var double NelsonSiegelSvensson::b0_
 * @brief Themodel's parameter beta 0. 
 */

 /**
 * @var double NelsonSiegelSvensson::b1_
 * @brief The model's parameter beta 1. 
 */

 /**
 * @var double NelsonSiegelSvensson::b2_
 * @brief The model's parameter beta 2. 
 */

 /**
 * @var double NelsonSiegelSvensson::b3_
 * @brief The model's parameter beta 3. 
 */

/**
 * @var double NelsonSiegelSvensson::tau1_
 * @brief The model's parameter tau 1. 
 */

/**
 * @var double NelsonSiegelSvensson::tau2_
 * @brief The model's parameter tau 2. 
 */

/** 
 * @brief The main constructor
 * @param b0 The model's parameter beta 0.
 * @param b1 The model's parameter beta 1.
 * @param b2 The model's parameter beta 2. 
 * @param b3 The model's parameter beta 3. 
 * @param tau1 The model's parameter tau 1. 
 * @param tau2 The model's parameter tau 2. 
 */
 NelsonSiegelSvensson::NelsonSiegelSvensson(double b0, double b1, double b2, double b3, double tau1, double tau2): 
    b0_(b0),b1_(b1),b2_(b2),b3_(b3),tau1_(tau1),tau2_(tau2){};

/**
 * @param t The year fraction to evaluate the model from.
 * @return The corresponding rate. 
 */
double NelsonSiegelSvensson::get_rate(double t)
{
   double tt1 = t/tau1_; 
   double tt2 = t/tau2_; 
   return b0_ + b1_*(1-exp(-tt1))/tt1 + b2_*((1-exp(-tt1))/tt1 - exp(-tt1)) + b3_*((1-exp(-tt2))/tt2 - exp(-tt2));
};