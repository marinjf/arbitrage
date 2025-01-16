#include "futures.h"

/**
 * @file futures.h
 * @brief Contains the implementation of Future and StructuredFuture classes.
 */

/**
 * @class Future
 * @brief Represents a financial future contract with an expiry date.
 */

/**
 * @brief Constructs a Future object as a perpetual future.
 * @param id The instrument's id. 
 */
Future::Future(const std::string id): 
    Instrument(id), is_perpetual_(true), expiry_ptr(nullptr), day_count_(DayCountConvention::ACT360){};

/**
 * @brief Constructs a Future object with the given expiry date (as a term future).
 * @param id The instrument's id. 
 * @param expiry A shared pointer to a DateTime object representing the expiry date.
 * @param day_count The day count convention to be used for the future. 
 * 
 * @see DayCountConvention
 */
Future::Future(
    const std::string id,
    const std::shared_ptr<DateTime> expiry, 
    const DayCountConvention day_count): 
    Instrument(id), is_perpetual_(false), expiry_ptr(expiry), day_count_(day_count){};

/**
 * @brief Retrieves the expiry date pointer for the future.
 * @return A shared pointer to the DateTime object representing the expiry date.
 */
std::shared_ptr<DateTime> Future::get_expiry()
{
    return expiry_ptr;
};

/**
 * @brief Retrieves the expiry date pointer for the future.
 * @return A shared pointer to the DateTime object representing the expiry date.
 */
DayCountConvention Future::get_day_count()
{
    return day_count_;
};

/**
 * @brief Retrieves if the future is perpetual or not.
 * @return A boolean value: true if perpetual, false else.
 */
bool Future::is_perpetual()
{
    return is_perpetual_;
};

/**
 * @class StructuredFutureMismatchError
 * @brief Exception class for mismatched weights and futures in StructuredFuture.
 */

/**
 * @brief Returns the error message for a mismatch between weights and futures.
 * @return A C-string containing the error message.
 */
const char * StructuredFutureMismatchError::what() const throw(){
    return "The number of weights and the number of futures must match.";
};

/**
 * @class StructuredFuture
 * @brief Represents a collection of futures and their associated weights.
 */

/**
 * @brief Constructs a StructuredFuture object.
 *
 * This constructor initializes the StructuredFuture object with a list of futures
 * and their corresponding weights. It also performs a consistency check to ensure
 * the number of weights matches the number of futures.
 *
 * @param futures A vector of shared pointers to Future objects.
 * @param weights A vector of weights associated with the futures.
 * @throw StructuredFutureMismatchError If the number of weights does not match the number of futures.
 */
StructuredFuture::StructuredFuture(
    const std::string id,
    const std::vector<std::shared_ptr<Future>> futures, 
    const std::vector<double> weights): 
    Instrument(id), weights_(weights), futures_(futures)
{
    check();
}

/**
 * @brief Retrieves the list of futures.
 * @return A vector of shared pointers to Future objects.
 */
std::vector<std::shared_ptr<Future>> StructuredFuture::get_futures()
{
    return futures_;
};

/**
 * @brief Retrieves the list of weights.
 * @return A vector of weights associated with the futures.
 */
std::vector<double> StructuredFuture::get_weights()
{
    return weights_; 
};

/**
 * @brief Performs a consistency check on the weights and futures.
 *
 * Ensures that the number of weights matches the number of futures.
 * If the numbers do not match, an exception is thrown.
 *
 * @throw StructuredFutureMismatchError If the number of weights does not match the number of futures.
 */
void StructuredFuture::check()
{
    if (weights_.size() != futures_.size()){
        throw StructuredFutureMismatchError();
    }
};
