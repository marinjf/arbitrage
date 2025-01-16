#pragma once
#include <iostream>

class Currency
{ 
    public: 
        std::string get_code(); 
        std::string get_name();
        Currency(
            const std::string code, 
            const std::string name);
        ~Currency(){};
    private: 
        const std::string code_;
        const std::string name_;
};

class RiskFactor
{ 
    public: 
        std::string get_id(); 
        std::shared_ptr<Currency> get_base_currency();
        RiskFactor(
            const std::string id,
            const std::shared_ptr<Currency> base_currency
        );
        virtual ~RiskFactor(){};
    private: 
        const std::string id_;
        const std::shared_ptr<Currency> base_ccy_ptr;
};

class InterestRate: public RiskFactor 
{
    public:
        InterestRate(
            const std::string id,
            const std::shared_ptr<Currency> base_currency
        );
        ~InterestRate(){};
};

class FX: public RiskFactor
{
    public: 
        std::shared_ptr<Currency> get_domestic_currency();
        std::shared_ptr<Currency> get_foreign_currency();
        FX(
            const std::shared_ptr<Currency> foreign_currency, 
            const std::shared_ptr<Currency> domestic_currency
        );
        ~FX(){};
    private: 
        const std::shared_ptr<Currency> counter_ccy_ptr;
        std::string generate_id(
            const std::shared_ptr<Currency> foreign_currency, 
            const std::shared_ptr<Currency> domestic_currency
        ); 
};

class Crypto: public RiskFactor
{
    public: 
        std::shared_ptr<Currency> get_domestic_currency();
        std::shared_ptr<Currency> get_foreign_currency();
        Crypto(
            const std::shared_ptr<Currency> foreign_currency, 
            const std::shared_ptr<Currency> domestic_currency
        );
        ~Crypto(){};
    private: 
        const std::shared_ptr<Currency> counter_ccy_ptr;
        std::string generate_id(
            const std::shared_ptr<Currency> foreign_currency, 
            const std::shared_ptr<Currency> domestic_currency
        ); 
};


