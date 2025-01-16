#include "cryptoassets.h"

/**
 * @file cryptoassets.cpp
 * @brief Implementation of CryptoAsset and its derived classes.
 */

/**
 * @class CryptoAsset
 * @brief Represents a generic cryptocurrency asset.
 */

/**
 * @brief Constructs a CryptoAsset object.
 * @param id The asset's id.
 * @param crypto A shared pointer to the Crypto object.
 * @param quote_currency A shared pointer to the Currency object.
 */
CryptoAsset::CryptoAsset(
    const std::string id,
    const std::shared_ptr<Crypto> crypto, 
    const std::shared_ptr<Currency> quote_currency
): 
    Asset(id, quote_currency, crypto){}; 

/**
 * @class CryptoSpot
 * @brief Represents a spot cryptocurrency asset.
 */

/**
 * @brief Constructs a CryptoSpot object.
 * @param id The asset's id.
 * @param crypto A shared pointer to the Crypto object.
 * @param quote_currency A shared pointer to the Currency object.
 */
CryptoSpot::CryptoSpot(
    const std::string id,
    const std::shared_ptr<Crypto> crypto, 
    const std::shared_ptr<Currency> quote_currency
): 
    CryptoAsset(id, crypto, quote_currency){}; 

/**
 * @class CryptoFuture
 * @brief Represents a cryptocurrency future.
 */

/**
 * @brief Constructs a CryptoFuture object.
 * @param id The asset's id.
 * @param crypto A shared pointer to the Crypto object.
 * @param quote_currency A shared pointer to the Currency object.
 * @param future A shared pointer to the Future object.
 */
CryptoFuture::CryptoFuture(
    const std::string id,
    const std::shared_ptr<Crypto> crypto, 
    const std::shared_ptr<Currency> quote_currency, 
    const std::shared_ptr<Future> future
): 
    CryptoAsset(id, crypto, quote_currency), future_ptr(future){}; 

/**
 * @brief Retrieves the associated Future object.
 * @return A shared pointer to the Future object.
 */
std::shared_ptr<Future> CryptoFuture::get_future()
{
    return future_ptr;
}; 

/**
 * @brief Checks if the future is perpetual.
 * @return True if the future is perpetual, otherwise false.
 */
bool CryptoFuture::is_perpetual()
{
    return future_ptr->is_perpetual();
}; 

/**
 * @brief Retrieves the expiry date of the future.
 * @return A shared pointer to the DateTime object representing the expiry date.
 */
std::shared_ptr<DateTime> CryptoFuture::get_expiry_datetime()
{
    return future_ptr->get_expiry();
};

/**
 * @class CryptoStructuredFuture
 * @brief Represents a structured cryptocurrency future.
 */

/**
 * @brief Constructs a CryptoStructuredFuture object.
 * @param id The asset's id.
 * @param crypto A shared pointer to the Crypto object.
 * @param quote_currency A shared pointer to the Currency object.
 * @param structured_future A shared pointer to the StructuredFuture object.
 * @throw StructuredFutureMismatchError
 */
CryptoStructuredFuture::CryptoStructuredFuture(
    const std::string id,
    const std::shared_ptr<Crypto> crypto, 
    const std::shared_ptr<Currency> quote_currency, 
    const std::shared_ptr<StructuredFuture> structured_future
): 
    CryptoAsset(id, crypto, quote_currency), structured_future_ptr(structured_future){};

/**
 * @brief Retrieves the associated StructuredFuture object.
 * @return A shared pointer to the StructuredFuture object.
 */
std::shared_ptr<StructuredFuture> CryptoStructuredFuture::get_structured_future()
{
    return structured_future_ptr;
}; 

/**
 * @class CryptoVolatilityFuture
 * @brief Represents a volatility cryptocurrency future.
 */

/**
 * @brief Constructs a CryptoVolatilityFuture object.
 * @param id The asset's id.
 * @param crypto A shared pointer to the Crypto object.
 * @param quote_currency A shared pointer to the Currency object.
 * @param expiry A shared pointer to the DateTime object representing the expiry date.
 */
CryptoVolatilityFuture::CryptoVolatilityFuture(
    const std::string id,
    const std::shared_ptr<Crypto> crypto, 
    const std::shared_ptr<Currency> quote_currency, 
    const std::shared_ptr<DateTime> expiry, 
    const DayCountConvention day_count
): 
    CryptoAsset(id, crypto, quote_currency), future_ptr(set_future(id, expiry, day_count)){}; 

/**
 * @brief Retrieves the associated Future object.
 * @return A shared pointer to the Future object.
 */
std::shared_ptr<Future> CryptoVolatilityFuture::get_future()
{
    return future_ptr;
}; 

/**
 * @brief Retrieves the expiry date of the future.
 * @return A shared pointer to the DateTime object representing the expiry date.
 */
std::shared_ptr<DateTime> CryptoVolatilityFuture::get_expiry_datetime()
{
    return future_ptr->get_expiry();
};

/**
 * @brief Sets the Future object based on the expiry date.
 * @param expiry A shared pointer to the DateTime object representing the expiry date.
 * @return A shared pointer to the newly created Future object.
 */
std::shared_ptr<Future> CryptoVolatilityFuture::set_future(
    const std::string id,
    const std::shared_ptr<DateTime> expiry, 
    const DayCountConvention day_count)
{
    return std::make_shared<Future>(id, expiry, day_count);
}; 

/**
 * @class CryptoOption
 * @brief Represents a cryptocurrency option.
 */

/**
 * @brief Constructs a CryptoOption object with a spot underlying asset.
 * @param id The asset's id.
 * @param crypto A shared pointer to the Crypto object.
 * @param quote_currency A shared pointer to the Currency object.
 * @param option A shared pointer to the Option object.
 */
CryptoOption::CryptoOption(
    const std::string id,
    const std::shared_ptr<Crypto> crypto, 
    const std::shared_ptr<Currency> quote_currency, 
    const std::shared_ptr<Option> option
): 
    CryptoAsset(id, crypto, quote_currency), 
    underlying_crypto_asset(std::make_shared<CryptoSpot>(id, crypto, quote_currency)), 
    option_ptr(option){};

/**
 * @brief Constructs a CryptoOption object with a future underlying asset.
 * @param id The asset's id.
 * @param crypto A shared pointer to the Crypto object.
 * @param quote_currency A shared pointer to the Currency object.
 * @param option A shared pointer to the Option object.
 * @param future A shared pointer to the Future object.
 */
CryptoOption::CryptoOption(
    const std::string id,
    const std::shared_ptr<Crypto> crypto, 
    const std::shared_ptr<Currency> quote_currency, 
    const std::shared_ptr<Option> option, 
    const std::shared_ptr<Future> future
): 
    CryptoAsset(id, crypto, quote_currency), 
    underlying_crypto_asset(std::make_shared<CryptoFuture>(id, crypto, quote_currency, future)), 
    option_ptr(option){};

/**
 * @brief Retrieves the associated Option object.
 * @return A shared pointer to the Option object.
 */
std::shared_ptr<Option> CryptoOption::get_option()
{
    return option_ptr;
}; 

/**
 * @brief Retrieves the underlying crypto asset.
 * @return A shared pointer to the underlying CryptoAsset object.
 */
std::shared_ptr<CryptoAsset> CryptoOption::get_underlying_crypto_asset()
{
    return underlying_crypto_asset;
};

/**
 * @class CryptoStructuredOption
 * @brief Represents a structured cryptocurrency option.
 */

/**
 * @brief Constructs a CryptoStructuredOption object.
 * @param id The asset's id.
 * @param crypto A shared pointer to the Crypto object.
 * @param quote_currency A shared pointer to the Currency object.
 * @param structured_option A shared pointer to the StructuredOption object.
 * @throw StructuredOptionMismatchError
 */
CryptoStructuredOption::CryptoStructuredOption(
    const std::string id,
    const std::shared_ptr<Crypto> crypto, 
    const std::shared_ptr<Currency> quote_currency, 
    const std::shared_ptr<StructuredOption> structured_option
): 
    CryptoAsset(id, crypto, quote_currency), 
    underlying_crypto_asset(std::make_shared<CryptoSpot>(id, crypto, quote_currency)),
    structured_option_ptr(structured_option)
    {};

/**
 * @brief Constructs a CryptoStructuredOption object.
 * @param id The asset's id.
 * @param crypto A shared pointer to the Crypto object.
 * @param quote_currency A shared pointer to the Currency object.
 * @param structured_option A shared pointer to the StructuredOption object.
 * @param future A shared pointer to the Future object.
 * @throw StructuredOptionMismatchError
 */
CryptoStructuredOption::CryptoStructuredOption(
    const std::string id,
    const std::shared_ptr<Crypto> crypto, 
    const std::shared_ptr<Currency> quote_currency, 
    const std::shared_ptr<StructuredOption> structured_option,
    const std::shared_ptr<Future> future
): 
    CryptoAsset(id, crypto, quote_currency), 
    underlying_crypto_asset(std::make_shared<CryptoFuture>(id, crypto, quote_currency, future)),
    structured_option_ptr(structured_option)
    {};

/**
 * @brief Retrieves the associated StructuredOption object.
 * @return A shared pointer to the StructuredOption object.
 */
std::shared_ptr<StructuredOption> CryptoStructuredOption::get_structured_option()
{
    return structured_option_ptr;
};

/**
 * @brief Retrieves the underlying crypto asset.
 * @return A shared pointer to the underlying CryptoAsset object.
 */
std::shared_ptr<CryptoAsset> CryptoStructuredOption::get_underlying_crypto_asset()
{
    return underlying_crypto_asset;
};
