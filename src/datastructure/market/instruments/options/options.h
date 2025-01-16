#pragma once
#include <iostream>
#include <vector>
#include "../../../../../src/datastructure/datetime/datetime.h"
#include "../../../../../src/datastructure/market/riskfactors/riskfactors.h"
#include "../../../../../src/datastructure/market/instruments/interface.h"

enum OptionType {CALL = 1, PUT = -1};

enum ExerciseType {AMERICAN, EUROPEAN, BERMUDAN};

enum BarrierType 
{
    UP_AND_IN, 
    UP_AND_OUT, 
    DOWN_AND_IN, 
    DOWN_AND_OUT, 
    DOUBLE_KNOCK_IN, 
    DOUBLE_KNOCK_OUT 
};

class Option : public Instrument
{
    public:
        double get_strike();
        OptionType get_option_type();
        std::shared_ptr<DateTime> get_expiry();
        DayCountConvention get_day_count();
        std::shared_ptr<Currency> get_strike_currency();
        Option(
            const std::string id,
            const std::shared_ptr<DateTime> expiry, 
            const OptionType type, 
            const double strike, 
            const DayCountConvention day_count, 
            const std::shared_ptr<Currency> strike_currency);
        virtual ~Option() = default;
    private: 
        const double K; 
        const std::shared_ptr<Currency> strike_ccy_ptr;
        const OptionType type_; 
        const std::shared_ptr<DateTime> expiry_ptr; 
        const DayCountConvention day_count_; 
};

class StructuredOptionMismatchError: public std::exception 
{public: const char * what() const throw();};

class StructuredOption : public Instrument
{
    public:
        std::vector<std::shared_ptr<Option>> get_options();
        std::vector<double> get_weights();
        StructuredOption(
            const std::string id,
            const std::vector<std::shared_ptr<Option>> options, 
            const std::vector<double> weights);
        virtual ~StructuredOption() = default;
    private: 
        void check();
        const std::vector<double> weights_; 
        const std::vector<std::shared_ptr<Option>> options_; 
};

class EuropeanVanillaOption : public Option
{
    public: 
        EuropeanVanillaOption(
            const std::string id,
            const std::shared_ptr<DateTime> expiry, 
            const OptionType type, 
            const double strike, 
            const DayCountConvention day_count, 
            const std::shared_ptr<Currency> strike_currency);
        ~EuropeanVanillaOption() = default;
}; 

class AmericanVanillaOption : public Option
{
    public:
        AmericanVanillaOption(
            const std::string id,
            const std::shared_ptr<DateTime> expiry, 
            const OptionType type, 
            const double strike, 
            const DayCountConvention day_count, 
            const std::shared_ptr<Currency> strike_currency);
        ~AmericanVanillaOption() = default;
}; 

