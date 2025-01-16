#pragma once
#include <iostream>
#include <vector>
#include "../../../../../src/datastructure/datetime/datetime.h"
#include "../../../../../src/datastructure/market/instruments/interface.h"

class Future : public Instrument
{
    public:
        bool is_perpetual();
        std::shared_ptr<DateTime> get_expiry();
        DayCountConvention get_day_count();
        Future(const std::string id);
        Future(
            const std::string id,
            const std::shared_ptr<DateTime> expiry, 
            const DayCountConvention day_count);
        ~Future() = default;
    private: 
        const bool is_perpetual_;
        const std::shared_ptr<DateTime> expiry_ptr; 
        const DayCountConvention day_count_;
};

class StructuredFutureMismatchError: public std::exception 
{public: const char * what() const throw();};

class StructuredFuture : public Instrument
{
    public:
        std::vector<std::shared_ptr<Future>> get_futures();
        std::vector<double> get_weights();
        StructuredFuture(
            const std::string id,
            const std::vector<std::shared_ptr<Future>> futures, 
            const std::vector<double> weights);
        ~StructuredFuture() = default;
    private: 
        void check();
        const std::vector<double> weights_; 
        const std::vector<std::shared_ptr<Future>> futures_; 
};

