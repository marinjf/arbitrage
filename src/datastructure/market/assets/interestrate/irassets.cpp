#include "irassets.h"

/**
 * @class InterestRateAsset
 * @brief Represents a financial asset associated with an interest rate.
 *
 * Constructs an InterestRateAsset with a given interest rate.
 * @param id The asset's id. 
 * @param interest_rate Shared pointer to an InterestRate object.
 */
InterestRateAsset::InterestRateAsset(
    const std::string id,
    const std::shared_ptr<InterestRate> interest_rate): 
    Asset(id, interest_rate->get_base_currency(), interest_rate), interest_rate_ptr(interest_rate){}; 

/**
 * @class ZeroCouponBond
 * @brief Represents a zero-coupon bond, a type of InterestRateAsset.
 *
 * Constructs a ZeroCouponBond using an interest rate, day count convention, and expiry date.
 * @param id The asset's id. 
 * @param interest_rate Shared pointer to an InterestRate object.
 * @param day_count_convention The day count convention to be used.
 * @param expiry_datetime Shared pointer to a DateTime object representing the expiry date.
 */
ZeroCouponBond::ZeroCouponBond(
    const std::string id,
    const std::shared_ptr<InterestRate> interest_rate,  
    const DayCountConvention day_count_convention, 
    const std::shared_ptr<DateTime> expiry_datetime): 
    InterestRateAsset(id, interest_rate), 
    day_count_convention_(day_count_convention),
    expiry_ptr(expiry_datetime){};

/**
 * @brief Constructs a ZeroCouponBond using an expiry tenor and start date.
 * @param id The asset's id. 
 * @param interest_rate Shared pointer to an InterestRate object.
 * @param day_count_convention The day count convention to be used.
 * @param expiry_tenor The tenor until expiry.
 * @param start_datetime Shared pointer to a DateTime object representing the start date.
 * @see get_end_datetime_from_tenor
 */
ZeroCouponBond::ZeroCouponBond(
    const std::string id,
    const std::shared_ptr<InterestRate> interest_rate,  
    const DayCountConvention day_count_convention, 
    const Tenor expiry_tenor, 
    const std::shared_ptr<DateTime> start_datetime): 
    InterestRateAsset(id, interest_rate), 
    day_count_convention_(day_count_convention),
    expiry_ptr(get_end_datetime_from_tenor(start_datetime, expiry_tenor, day_count_convention)){};

/**
 * @brief Returns the day count convention used by the bond.
 * @return The day count convention of the bond.
 */
DayCountConvention ZeroCouponBond::get_day_count_convention()
{
    return day_count_convention_;
};

/**
 * @brief Retrieves the expiry date of the bond.
 * @return Shared pointer to a DateTime object representing the expiry date.
 */
std::shared_ptr<DateTime> ZeroCouponBond::get_expiry_datetime()
{
    return expiry_ptr;
};

/**
 * @brief Calculates the year fraction between a reference date and the bond's expiry date.
 *
 * @param reference_datetime Shared pointer to a DateTime object representing the reference date.
 * @return The year fraction between the reference date and the expiry date.
 * @see get_year_fraction_from_datetimes
 * @throws UndefinedDayCountConventionError if the day count convention is invalid.
 * @throws NonPositiveYearFraction if the reference datetime is after the exppiry date. 
 */
double ZeroCouponBond::get_year_fraction(std::shared_ptr<DateTime> reference_datetime)
{
    return get_year_fraction_from_datetimes(
        reference_datetime, 
        get_expiry_datetime(), 
        day_count_convention_
    );
};
