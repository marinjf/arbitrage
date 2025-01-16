#pragma once
#include <iostream>
#include <vector>
#include "../../../../../src/datastructure/market/assets/interface.h"
#include "../../../../../src/datastructure/market/riskfactors/riskfactors.h"
#include "../../../../../src/datastructure/datetime/datetime.h"
#include "../../../../../src/datastructure/market/instruments/options/options.h"
#include "../../../../../src/datastructure/market/instruments/futures/futures.h"

class CryptoAsset : public Asset 
{
    public: 
        CryptoAsset(
            const std::string id,
            const std::shared_ptr<Crypto> crypto, 
            const std::shared_ptr<Currency> quote_currency);
        virtual ~CryptoAsset() = default; 
};

class CryptoSpot : public CryptoAsset 
{
    public: 
        CryptoSpot(
            const std::string id,
            const std::shared_ptr<Crypto> crypto, 
            const std::shared_ptr<Currency> quote_currency);
        ~CryptoSpot() = default; 
};

class CryptoFuture : public CryptoAsset 
{
    public: 
        std::shared_ptr<Future> get_future();
        bool is_perpetual(); 
        std::shared_ptr<DateTime> get_expiry_datetime();
        CryptoFuture(
            const std::string id,
            const std::shared_ptr<Crypto> crypto, 
            const std::shared_ptr<Currency> quote_currency, 
            const std::shared_ptr<Future> future);
        ~CryptoFuture() = default; 
    private: 
        const std::shared_ptr<Future> future_ptr;

};

class CryptoStructuredFuture : public CryptoAsset
{
    public: 
        std::shared_ptr<StructuredFuture> get_structured_future();
        CryptoStructuredFuture(
            const std::string id,
            const std::shared_ptr<Crypto> crypto, 
            const std::shared_ptr<Currency> quote_currency, 
            const std::shared_ptr<StructuredFuture> structured_future);
        ~CryptoStructuredFuture() = default; 
    private: 
        const std::shared_ptr<StructuredFuture> structured_future_ptr;
};

class CryptoVolatilityFuture : public CryptoAsset 
{
    public: 
        std::shared_ptr<Future> get_future();
        std::shared_ptr<DateTime> get_expiry_datetime();
        CryptoVolatilityFuture(
            const std::string id,
            const std::shared_ptr<Crypto> crypto, 
            const std::shared_ptr<Currency> quote_currency, 
            const std::shared_ptr<DateTime> expiry, 
            const DayCountConvention day_count);
        ~CryptoVolatilityFuture() = default;
    private: 
        std::shared_ptr<Future> set_future(
            const std::string id,
            const std::shared_ptr<DateTime> expiry, 
            const DayCountConvention day_count);
        const std::shared_ptr<Future> future_ptr;  
};

class CryptoOption : public CryptoAsset
{
    public: 
        std::shared_ptr<Option> get_option();
        std::shared_ptr<CryptoAsset> get_underlying_crypto_asset();
        CryptoOption(
            const std::string id,
            const std::shared_ptr<Crypto> crypto, 
            const std::shared_ptr<Currency> quote_currency, 
            const std::shared_ptr<Option> option);
        CryptoOption(
            const std::string id,
            const std::shared_ptr<Crypto> crypto, 
            const std::shared_ptr<Currency> quote_currency, 
            const std::shared_ptr<Option> option, 
            const std::shared_ptr<Future> future);
        ~CryptoOption() = default;
    private: 
        const std::shared_ptr<CryptoAsset> underlying_crypto_asset; 
        const std::shared_ptr<Option> option_ptr; 
}; 

class CryptoStructuredOption : public CryptoAsset
{
    public: 
        std::shared_ptr<StructuredOption> get_structured_option();
        std::shared_ptr<CryptoAsset> get_underlying_crypto_asset();
        CryptoStructuredOption(
            const std::string id,
            const std::shared_ptr<Crypto> crypto, 
            const std::shared_ptr<Currency> quote_currency, 
            const std::shared_ptr<StructuredOption> structured_option);
        CryptoStructuredOption(
            const std::string id,
            const std::shared_ptr<Crypto> crypto, 
            const std::shared_ptr<Currency> quote_currency, 
            const std::shared_ptr<StructuredOption> structured_option, 
            const std::shared_ptr<Future> future);
        ~CryptoStructuredOption() = default; 
    private: 
        const std::shared_ptr<CryptoAsset> underlying_crypto_asset; 
        const std::shared_ptr<StructuredOption> structured_option_ptr;
};

