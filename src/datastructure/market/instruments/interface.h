#pragma once
#include <iostream>
#include <typeinfo>

class Instrument
{
    public: 
        std::string get_id();
        std::string get_instrument_type() const;
        Instrument(const std::string id);
        virtual ~Instrument(){};
    private: 
        const std::string id_;
};

