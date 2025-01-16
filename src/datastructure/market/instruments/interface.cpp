#include "interface.h"

#if defined(__GNUG__)
    #include <cxxabi.h>
    #include <memory>
#endif

/**
 * @class Instrument
 * @brief Represents a financial instrument (future, option).
 */

/**
 * @brief Constructor for the Instrument class.
 * @param id The instrument ID.
 */
Instrument::Instrument(const std::string id):id_(id){}; 

/**
 * @brief Gets the instrument's id.
 * @return The instrument's id.
 */
std::string Instrument::get_id()
{
    return id_;
};

/**
 * @brief Gets the instrument's type. It also handles possible mangled names. 
 * @return The instrument's type.
 */
std::string Instrument::get_instrument_type() const
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
}