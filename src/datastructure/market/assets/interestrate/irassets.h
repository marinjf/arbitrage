#pragma once
#include <iostream>
#include "../../../../../src/datastructure/market/assets/interface.h"
#include "../../../../../src/datastructure/market/riskfactors/riskfactors.h"
#include "../../../../../src/datastructure/datetime/datetime.h"

class InterestRateAsset: public Asset
{
    public: 
        InterestRateAsset(
            const std::string id, 
            const std::shared_ptr<InterestRate> interest_rate);
        virtual ~InterestRateAsset(){} 
    private: 
        const std::shared_ptr<InterestRate> interest_rate_ptr;
}; 

class ZeroCouponBond: public InterestRateAsset
{
    public:
        DayCountConvention get_day_count_convention(); 
        std::shared_ptr<DateTime> get_expiry_datetime();
        double get_year_fraction(std::shared_ptr<DateTime> reference_datetime);
        ZeroCouponBond(
            const std::string id,
            const std::shared_ptr<InterestRate> interest_rate, 
            const DayCountConvention day_count_convention,
            const std::shared_ptr<DateTime> expiry_datetime
        );
        ZeroCouponBond(
            const std::string id,
            const std::shared_ptr<InterestRate> interest_rate, 
            const DayCountConvention day_count_convention,
            const Tenor expiry_tenor, 
            const std::shared_ptr<DateTime> start_datetime
        );
        ~ZeroCouponBond(){};
    private: 
        const DayCountConvention day_count_convention_;
        const std::shared_ptr<DateTime> expiry_ptr;
        
}; 




