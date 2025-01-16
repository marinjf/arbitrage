#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <typeinfo>
#include "../../../../src/datastructure/market/riskfactors/riskfactors.h"

class Asset
{
    public: 
        std::string get_id();
        std::shared_ptr<Currency> get_quote_currency();
        std::shared_ptr<RiskFactor> get_risk_factor();
        bool is_quanto(); 
        std::shared_ptr<FX> get_fx_quanto_risk_factor(); 
        std::string get_asset_type() const;
        Asset(
            const std::string id,
            const std::shared_ptr<Currency> quote_currency,
            const std::shared_ptr<RiskFactor> risk_factor
        );
        virtual ~Asset(){};
    private: 
        const std::string id_;
        const std::shared_ptr<Currency> quote_ccy_ptr_;
        const std::shared_ptr<RiskFactor> risk_factor_ptr_;
};

class AssetQuote
{
    public: 
        std::shared_ptr<Asset> get_asset(); 
        double get_bid(); 
        double get_ask(); 
        double get_absolute_spread(); 
        double get_relative_spread(); 
        AssetQuote(
            const std::shared_ptr<Asset> asset,
            const double bid,
            const double ask);
        virtual ~AssetQuote(){};
    private: 
        const std::shared_ptr<Asset> asset_;
        const double bid_; 
        const double ask_;
};




