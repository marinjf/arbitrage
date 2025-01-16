#include "riskfactors.h"

/**
 * @class Currency
 * @brief Represents a currency with a unique code.
 */

/**
 * @brief Constructor for the Currency class.
 * @param code The unique code for the currency.
 */
Currency::Currency(const std::string code, const std::string name) : 
    code_(code), name_(name){};

/**
 * @brief Gets the unique code of the currency.
 * @return The unique currency code as a string.
 */
std::string Currency::get_code()
{
    return code_;
};

/**
 * @brief Gets the name of the currency.
 * @return The currency's name as a string.
 */
std::string Currency::get_name()
{
    return name_;
};

/**
 * @class RiskFactor
 * @brief Represents a generic financial risk factor.
 */

/**
 * @brief Constructor for the RiskFactor class.
 * @param id The unique identifier for the risk factor.
 * @param base_currency A shared pointer to the base currency of the risk factor.
 */
RiskFactor::RiskFactor(
    const std::string id,
    const std::shared_ptr<Currency> base_currency
) : 
    id_(id), base_ccy_ptr(base_currency) {};

/**
 * @brief Gets the unique identifier of the risk factor.
 * @return The risk factor's ID as a string.
 */
std::string RiskFactor::get_id()
{
    return id_;
};

/**
 * @brief Gets the base currency of the risk factor.
 * @return A shared pointer to the base currency.
 */
std::shared_ptr<Currency> RiskFactor::get_base_currency()
{
    return base_ccy_ptr;
};

/**
 * @class InterestRate
 * @brief Represents an interest rate as a type of risk factor.
 */

/**
 * @brief Constructor for the InterestRate class.
 * @param id The unique identifier for the interest rate.
 * @param base_currency A shared pointer to the base currency for the interest rate.
 */
InterestRate::InterestRate(
    const std::string id, 
    const std::shared_ptr<Currency> base_currency
) : RiskFactor(id, base_currency) {};

/**
 * @class FX
 * @brief Represents a foreign exchange (FX) rate as a type of risk factor.
 */

/**
 * @brief Constructor for the FX class.
 * @param foreign_currency A shared pointer to the foreign currency in the FX pair.
 * @param domestic_currency A shared pointer to the domestic currency in the FX pair.
 */
FX::FX(
    const std::shared_ptr<Currency> foreign_currency, 
    const std::shared_ptr<Currency> domestic_currency
) :
    RiskFactor(generate_id(foreign_currency, domestic_currency), domestic_currency),
    counter_ccy_ptr(foreign_currency) {};

/**
 * @brief Gets the domestic currency in the FX pair.
 * @return A shared pointer to the domestic currency.
 */
std::shared_ptr<Currency> FX::get_domestic_currency()
{
    return get_base_currency();
};

/**
 * @brief Gets the foreign currency in the FX pair.
 * @return A shared pointer to the foreign currency.
 */
std::shared_ptr<Currency> FX::get_foreign_currency()
{
    return counter_ccy_ptr;
};

/**
 * @brief Generates a unique identifier for the FX risk factor.
 * @param foreign_currency A shared pointer to the foreign currency in the FX pair.
 * @param domestic_currency A shared pointer to the domestic currency in the FX pair.
 * @return A string identifier in the format "<foreign_code><domestic_code>".
 */
std::string FX::generate_id(
    const std::shared_ptr<Currency> foreign_currency, 
    const std::shared_ptr<Currency> domestic_currency
)
{
    return foreign_currency->get_code() + domestic_currency->get_code();
};

/**
 * @class Crypto
 * @brief Represents a cryptocurrency exchange rate as a type of risk factor.
 */

/**
 * @brief Constructor for the Crypto class.
 * @param foreign_currency A shared pointer to the foreign cryptocurrency in the pair.
 * @param domestic_currency A shared pointer to the domestic cryptocurrency in the pair.
 */
Crypto::Crypto(
    std::shared_ptr<Currency> foreign_currency, 
    std::shared_ptr<Currency> domestic_currency
) :
    RiskFactor(generate_id(foreign_currency, domestic_currency), domestic_currency),
    counter_ccy_ptr(foreign_currency) {};

/**
 * @brief Gets the domestic cryptocurrency in the pair.
 * @return A shared pointer to the domestic cryptocurrency.
 */
std::shared_ptr<Currency> Crypto::get_domestic_currency()
{
    return get_base_currency();
};

/**
 * @brief Gets the foreign cryptocurrency in the pair.
 * @return A shared pointer to the foreign cryptocurrency.
 */
std::shared_ptr<Currency> Crypto::get_foreign_currency()
{
    return counter_ccy_ptr;
};

/**
 * @brief Generates a unique identifier for the Crypto risk factor.
 * @param foreign_currency A shared pointer to the foreign cryptocurrency in the pair.
 * @param domestic_currency A shared pointer to the domestic cryptocurrency in the pair.
 * @return A string identifier in the format "<foreign_code><domestic_code>".
 */
std::string Crypto::generate_id(
    const std::shared_ptr<Currency> foreign_currency, 
    const std::shared_ptr<Currency> domestic_currency
)
{
    return foreign_currency->get_code() + domestic_currency->get_code();
};
