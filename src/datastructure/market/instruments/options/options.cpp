#include "options.h"


/**
 * @enum OptionType
 * @brief Enum representing the type of option (call or put).
 */

/**
 * @enum ExerciseType
 * @brief Enum representing the type of option exercise style.
 */

/**
 * @enum BarrierType
 * @brief Enum representing the type of barrier option.
 */

/**
 * @class Option
 * @brief Base class for financial options.
 */

/**
 * @brief Constructor for the Option class.
 * @param expiry Pointer to the expiry date of the option.
 * @param type Type of the option (call or put).
 * @param strike Strike price of the option.
 * @param daycount The day count onvention to be used. 
 * @param strike_currency The strike price's currency. 
 * 
 * @see DayCountConvention 
 * @see Currency
 */
Option::Option(
    const std::string id,
    const std::shared_ptr<DateTime> expiry, 
    const OptionType type, 
    const double strike, 
    const DayCountConvention day_count, 
    const std::shared_ptr<Currency> strike_currency): 
    Instrument(id), K(strike), strike_ccy_ptr(strike_currency), type_(type), 
    expiry_ptr(expiry), day_count_(day_count){};

/**
 * @brief Gets the strike price of the option.
 * @return Strike price as a double.
 */
double Option::get_strike()
{
    return K;
};

/**
 * @brief Gets the day count convention of the option.
 * @return The day count convention.
 * 
 * @see DayCountConvention
 */
DayCountConvention Option::get_day_count()
{
    return day_count_;
};

/**
 * @brief Gets the strike price currency of the option.
 * @return The strike price currency.
 * 
 * @see Currency
 */
std::shared_ptr<Currency> Option::get_strike_currency()
{
    return strike_ccy_ptr;
};

/**
 * @brief Gets the type of the option (call or put).
 * @return Option type as an OptionType enum.
 */
OptionType Option::get_option_type()
{
    return type_;
};

/**
 * @brief Gets a shared pointer to the expiry date of the option.
 * @return Shared pointer to the expiry date.
 */
std::shared_ptr<DateTime> Option::get_expiry()
{
    return expiry_ptr;
};

/**
 * @class EuropeanVanillaOption
 * @brief Class representing a European vanilla option.
 * @see Option
 */

/**
 * @brief Constructor for the EuropeanVanillaOption class.
 * @param expiry Pointer to the expiry date of the option.
 * @param type Type of the option (call or put).
 * @param strike Strike price of the option.
 * @param daycount The day count onvention to be used. 
 * @param strike_currency The strike price's currency. 
 * 
 * @see DayCountConvention 
 * @see Currency
 */
EuropeanVanillaOption::EuropeanVanillaOption(
    const std::string id,
    const std::shared_ptr<DateTime> expiry, 
    const OptionType type, 
    const double strike, 
    const DayCountConvention day_count, 
    const std::shared_ptr<Currency> strike_currency): 
    Option(id, expiry, type, strike, day_count, strike_currency)
    {};

/**
 * @class AmericanVanillaOption
 * @brief Class representing an American vanilla option.
 * @see Option
 */

/**
 * @brief Constructor for the AmericanVanillaOption class.
 * @param expiry Pointer to the expiry date of the option.
 * @param type Type of the option (call or put).
 * @param strike Strike price of the option.
 * @param daycount The day count onvention to be used. 
 * @param strike_currency The strike price's currency. 
 * 
 * @see DayCountConvention 
 * @see Currency
 */
AmericanVanillaOption::AmericanVanillaOption(
    const std::string id,
    const std::shared_ptr<DateTime> expiry, 
    const OptionType type, 
    const double strike, 
    const DayCountConvention day_count, 
    const std::shared_ptr<Currency> strike_currency): 
    Option(id, expiry, type, strike, day_count, strike_currency)
    {};

/**
 * @class StructuredOptionMismatchError
 * @brief Exception class for mismatched weights and options in StructuredOption.
 */

/**
 * @brief Returns the error message for a mismatch between weights and options.
 * @return A C-string containing the error message.
 */
const char * StructuredOptionMismatchError::what() const throw(){
    return "The number of weights and the number of options must match.";
};

/**
 * @class StructuredOption
 * @brief Represents a collection of options and their associated weights.
 */

/**
 * @brief Constructs a StructuredOption object.
 *
 * This constructor initializes the StructuredOption object with a list of options
 * and their corresponding weights. It also performs a consistency check to ensure
 * the number of weights matches the number of options.
 *
 * @param options A vector of shared pointers to Option objects.
 * @param weights A vector of weights associated with the options.
 * @throw StructuredOptionMismatchError If the number of weights does not match the number of options.
 */
StructuredOption::StructuredOption(
    const std::string id,
    const std::vector<std::shared_ptr<Option>> options, 
    const std::vector<double> weights): 
    Instrument(id), weights_(weights), options_(options)
{
    check();
}

/**
 * @brief Retrieves the list of options.
 * @return A vector of shared pointers to Option objects.
 */
std::vector<std::shared_ptr<Option>> StructuredOption::get_options()
{
    return options_;
};

/**
 * @brief Retrieves the list of weights.
 * @return A vector of weights associated with the options.
 */
std::vector<double> StructuredOption::get_weights()
{
    return weights_; 
};

/**
 * @brief Performs a consistency check on the weights and options.
 *
 * Ensures that the number of weights matches the number of options.
 * If the numbers do not match, an exception is thrown.
 *
 * @throw StructuredOptionMismatchError If the number of weights does not match the number of options.
 */
void StructuredOption::check()
{
    if (weights_.size() != options_.size()){
        throw StructuredOptionMismatchError();
    }
};
