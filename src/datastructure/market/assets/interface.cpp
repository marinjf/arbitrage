#include "interface.h"

#if defined(__GNUG__)
    #include <cxxabi.h>
    #include <memory>
#endif

/**
 * @class Asset
 * @brief Represents a financial asset with a quote currency and risk factor.
 */

/**
 * @brief Constructor for the Asset class.
 * @param id The asset ID.
 * @param quote_currency Shared pointer to the quote currency.
 * @param risk_factor Shared pointer to the risk factor associated with the asset.
 */
Asset::Asset(
    const std::string id,
    std::shared_ptr<Currency> quote_currency,
    std::shared_ptr<RiskFactor> risk_factor):
    id_(id),
    quote_ccy_ptr_(quote_currency), 
    risk_factor_ptr_(risk_factor){}; 

/**
 * @brief Gets the asset's id.
 * @return The asset's id.
 */
std::string Asset::get_id()
{
    return id_;
};

/**
 * @brief Gets the asset's type name.
 * @return The asset's type.
 */
std::string Asset::get_asset_type() const
{
    const char* mangled_name = typeid(*this).name();
#if defined(__GNUG__)  // GCC/Clang: Demangle the name
    int status = 0;
    std::unique_ptr<char, void(*)(void*)> demangled_name(
        abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status), std::free);
    return (status == 0) ? demangled_name.get() : mangled_name;
#else  // MSVC or other compilers: Return the name directly
    return mangled_name;
#endif
};

/**
 * @brief Gets the quote currency of the asset.
 * @return Shared pointer to the quote currency.
 */
std::shared_ptr<Currency> Asset::get_quote_currency()
{
    return quote_ccy_ptr_;
};

/**
 * @brief Gets the risk factor associated with the asset.
 * @return Shared pointer to the risk factor.
 */
std::shared_ptr<RiskFactor> Asset::get_risk_factor()
{
    return risk_factor_ptr_;
};

/**
 * @brief Determines whether the asset is a quanto asset.
 * @return True if the asset is a quanto, false otherwise.
 */
bool Asset::is_quanto()
{
    std::string base_ccy = risk_factor_ptr_->get_base_currency()->get_code();
    if (quote_ccy_ptr_->get_code()==base_ccy){return false;}
    else {return true;}
};

/**
 * @brief Gets the FX quanto risk factor for the asset.
 * @return Shared pointer to the FX risk factor.
 */
std::shared_ptr<FX> Asset::get_fx_quanto_risk_factor()
{
    return std::make_shared<FX>(
        quote_ccy_ptr_,
        risk_factor_ptr_->get_base_currency());
};

/**
 * @class AssetQuote
 * @brief Represents a quote for an asset with bid and ask prices.
 */

/**
 * @brief Constructor for the AssetQuote class.
 * @param asset Shared pointer to the associated asset.
 * @param bid Bid price of the asset.
 * @param ask Ask price of the asset.
 */
AssetQuote::AssetQuote(
    const std::shared_ptr<Asset> asset,
    const double bid,
    const double ask
):
    asset_(asset), bid_(bid), ask_(ask){}; 

/**
 * @brief Gets the associated asset.
 * @return Shared pointer to the asset.
 */
std::shared_ptr<Asset> AssetQuote::get_asset()
{
    return asset_;
};

/**
 * @brief Gets the bid price of the asset.
 * @return Bid price as a double.
 */
double AssetQuote::get_bid()
{
    return bid_;
};

/**
 * @brief Gets the ask price of the asset.
 * @return Ask price as a double.
 */
double AssetQuote::get_ask()
{
    return ask_;
};

/**
 * @brief Calculates the absolute spread of the asset quote.
 * @return Absolute spread as a double.
 */
double AssetQuote::get_absolute_spread()
{
    return ask_ - bid_;
};

/**
 * @brief Calculates the relative spread of the asset quote.
 * @return Relative spread as a double, or NaN if the bid price is zero.
 */
double AssetQuote::get_relative_spread()
{
    if (bid_==0.0){return NAN;}
    else{return get_absolute_spread()/bid_;}
};
