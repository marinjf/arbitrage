#include "datetime.h"

/**
 * @enum EpochTimestampType
 * @brief Enum representing different timestamp types based on their precision.
 * 
 * This enum provides values to represent the different timestamp types used for
 * representing time with various levels of precision. It can be used to specify
 * the precision when dealing with timestamps, from seconds to nanoseconds.
 */

/**
 * @enum Tenor
 * @brief Enum representing different time periods used in financial markets.
 * 
 * Tenor is typically used to define the maturity of a financial instrument,
 * such as the length of a bond, loan, or derivative contract. The different
 * tenors in this enum represent various time intervals ranging from overnight 
 * (ON) to 30 years (_30Y).
 */

/**
 * @enum DayCountConvention
 * @brief Enum representing different day count conventions used in financial calculations.
 * 
 * Day count conventions are used to determine the number of days between two dates
 * in financial markets, which is essential for calculating interest and other financial
 * metrics. The different conventions in this enum represent the most commonly used day
 * count rules: ACT/360, ACT/365, and ACT/364.
 */

/**
 * @brief Exception thrown when a negative timestamp value is encountered.
 * @return A message indicating that the timestamp cannot be negative.
 */
const char * NegativeEpochTimestampError::what() const throw(){
    return "A timestamp value cannot be negative.";
};

/**
 * @brief Exception thrown when the day count convention is not defined.
 * @return A message indicating that the day count convention has not been defined.
 */
const char * UndefinedDayCountConventionError::what() const throw(){
    return "The day count convention has not been defined either for its name or the number in days in a year/month.";
};

/**
 * @brief Exception thrown when the tenor is undefined.
 * @return A message indicating that the tenor has not been defined.
 */
const char * UndefinedTenorError::what() const throw(){
    return "The tenor has not been defined either for its name or the conversion into the number of days.";
};

/**
 * @brief Exception thrown when a non-positive year fraction is encountered.
 * @return A message indicating that the year fraction must be positive.
 */
const char * NonPositiveYearFractionError::what() const throw(){
    return "A year fraction has to be positive.";
};

/**
 * @brief Constructs a TimeDelta object with the specified time parameters.
 * 
 * @param days The number of days in the TimeDelta.
 * @param hours The number of hours in the TimeDelta.
 * @param minutes The number of minutes in the TimeDelta.
 * @param seconds The number of seconds in the TimeDelta.
 * @param milliseconds The number of milliseconds in the TimeDelta.
 * @param microseconds The number of microseconds in the TimeDelta.
 * @param nanoseconds The number of nanoseconds in the TimeDelta.
 */
TimeDelta::TimeDelta(
    long long days, 
    long long hours, 
    long long minutes, 
    long long seconds, 
    long long milliseconds, 
    long long microseconds, 
    long long nanoseconds): 
    d(days), h(hours), m(minutes), s(seconds), 
    ms(milliseconds), mcs(microseconds),
    ns(nanoseconds){};

/**
 * @brief Calculates the total time in seconds.
 * 
 * @return The total time in seconds.
 */
long long TimeDelta::get_total_seconds()
{
    int mcs_value = static_cast<int>(EpochTimestampType::MICROSECONDS);
    int ns_value = static_cast<int>(EpochTimestampType::NANOSECONDS);
    int ms_value = static_cast<int>(EpochTimestampType::MILLISECONDS);
    long long day_s = d*24*60*60; 
    long long hour_s = h*60*60; 
    long long min_s = m*60; 
    long long micros_s = round(mcs/mcs_value); 
    long long millis_s = round(ms/ms_value); 
    long long nanos_s = round(ns/ns_value); 
    long long total = s+day_s+hour_s+min_s+micros_s+millis_s+nanos_s;
    return total;
}

/**
 * @brief Calculates the total time in milliseconds.
 * 
 * @return The total time in milliseconds.
 */
long long TimeDelta::get_total_milliseconds()
{
    int mcs_value = static_cast<int>(EpochTimestampType::MICROSECONDS);
    int ns_value = static_cast<int>(EpochTimestampType::NANOSECONDS);
    int ms_value = static_cast<int>(EpochTimestampType::MILLISECONDS);
    long long day_s = d*24*60*60; 
    long long hour_s = h*60*60; 
    long long min_s = m*60; 
    long long total_seconds = s+day_s+hour_s+min_s;
    long long micros_ms = round(mcs*ms_value/mcs_value); 
    long long nanos_ms = round(ns*ms_value/ns_value); 
    long long total = total_seconds*1000 + ms + micros_ms + nanos_ms;
    return total;
}

/**
 * @brief Calculates the total time in microseconds.
 * 
 * @return The total time in microseconds.
 */
long long TimeDelta::get_total_microseconds()
{
    int mcs_value = static_cast<int>(EpochTimestampType::MICROSECONDS);
    int ns_value = static_cast<int>(EpochTimestampType::NANOSECONDS);
    long long day_s = d*24*60*60; 
    long long hour_s = h*60*60; 
    long long min_s = m*60; 
    long long total_seconds = s+day_s+hour_s+min_s;
    long long total_milliseconds = total_seconds*1000+ms;
    long long nanos_ms = round(ns*mcs_value/ns_value); 
    long long total = total_milliseconds*1000+mcs+nanos_ms;
    return total;
}

/**
 * @brief Calculates the total time in nanoseconds.
 * 
 * @return The total time in nanoseconds.
 */
long long TimeDelta::get_total_nanoseconds()
{
    long long day_s = d*24*60*60; 
    long long hour_s = h*60*60; 
    long long min_s = m*60; 
    long long total_seconds = s+day_s+hour_s+min_s;
    long long total_milliseconds = total_seconds*1000+ms;
    long long total_microseconds = total_milliseconds*1000+mcs;
    long long total = total_microseconds*1000+ns;
    return total;
}

/**
 * @brief Sets the number of days in the TimeDelta.
 * 
 * @param n The number of days to set.
 */
void TimeDelta::set_days(const long long n)
{
    d = n; 
};

/**
 * @brief Sets the number of hours in the TimeDelta.
 * 
 * @param n The number of hours to set.
 */
void TimeDelta::set_hours(const long long n)
{
    h = n; 
};

/**
 * @brief Sets the number of minutes in the TimeDelta.
 * 
 * @param n The number of minutes to set.
 */
void TimeDelta::set_minutes(const long long n)
{
    m = n; 
};

/**
 * @brief Sets the number of seconds in the TimeDelta.
 * 
 * @param n The number of seconds to set.
 */
void TimeDelta::set_seconds(const long long n)
{
    s = n; 
};

/**
 * @brief Sets the number of microseconds in the TimeDelta.
 * 
 * @param n The number of microseconds to set.
 */
void TimeDelta::set_microseconds(const long long n)
{
    mcs = n; 
};

/**
 * @brief Sets the number of milliseconds in the TimeDelta.
 * 
 * @param n The number of milliseconds to set.
 */
void TimeDelta::set_milliseconds(const long long n)
{
    ms = n; 
};

/**
 * @brief Sets the number of nanoseconds in the TimeDelta.
 * 
 * @param n The number of nanoseconds to set.
 */
void TimeDelta::set_nanoseconds(const long long n)
{
    ns = n; 
};

/**
 * @brief Constructs a DateTime object with a timestamp and timestamp type.
 * 
 * @param timestamp The timestamp value.
 * @param type The timestamp type.
 * @throws NegativeEpochTimestampError If the timestamp is negative.
 */
DateTime::DateTime(
    long long timestamp, 
    EpochTimestampType type): 
    tmsp(timestamp), type_(type)
{
    if (tmsp<0){throw NegativeEpochTimestampError();}
};

/**
 * @brief Gets the timestamp of the DateTime.
 * 
 * @return The timestamp value.
 */
long long DateTime::get_timestamp()
{
    return tmsp; 
};

/**
 * @brief Gets the timestamp type of the DateTime.
 * 
 * @return The timestamp type.
 */
EpochTimestampType DateTime::get_timestamp_type()
{
    return type_; 
};

/**
 * @brief Sets the timestamp value of the DateTime.
 * 
 * @param timestamp The new timestamp value to set.
 */
void DateTime::set_timestamp(const long long timestamp)
{
    tmsp = timestamp; 
};

/**
 * @brief Sets the timestamp type of the DateTime.
 * 
 * @param type The new timestamp type to set.
 */
void DateTime::set_timestamp_type(const EpochTimestampType type)
{
    type_ = type; 
};

/**
 * @brief Converts the timestamp to a different type and returns time information as a tm structure.
 * 
 * @return A unique pointer to a tm structure containing the time information.
 */
std::unique_ptr<std::tm> DateTime::get_time_info()
{
    EpochTimestampType old_tmsp_type = type_;
    convert_timestamp(EpochTimestampType::SECONDS);
    std::time_t timestamp = tmsp;
    convert_timestamp(old_tmsp_type);
    std::tm* time_info_ptr = std::localtime(&timestamp);
    return std::make_unique<std::tm>(*time_info_ptr);
};

/**
 * @brief Checks if the date falls on a weekend (Saturday or Sunday).
 * 
 * @return True if the date is a weekend, false otherwise.
 */
bool DateTime::is_week_end()
{
    std::unique_ptr<std::tm> time_info = get_time_info();
    if (time_info->tm_wday==0){return true;}
    if (time_info->tm_wday==6){return true;}
    return false;
};

/**
 * @brief Applies a TimeDelta to the DateTime.
 * 
 * @param dt A shared pointer to the TimeDelta object.
 */
void DateTime::apply_time_delta(const std::shared_ptr<TimeDelta> dt)
{
    switch(type_){
        case EpochTimestampType::SECONDS: 
        {
            tmsp += dt->get_total_seconds();
            break;
        }
        case EpochTimestampType::MILLISECONDS: 
        {
            tmsp += dt->get_total_milliseconds();
            break;
        }
        case EpochTimestampType::MICROSECONDS: 
        {
            tmsp += dt->get_total_microseconds();
            break;
        }
        case EpochTimestampType::NANOSECONDS: 
        {
            tmsp+=dt->get_total_nanoseconds();
            break;
        }
    }
};

/**
 * @brief Converts the timestamp to a new type.
 * 
 * @param type The new timestamp type to convert to.
 */
void DateTime::convert_timestamp(const EpochTimestampType type)
{
    long long type1 = static_cast<int>(type);
    long long type2 = static_cast<int>(type_);
    double factor = double(type1)/double(type2);
    long long new_tmsp = round(factor*tmsp);
    set_timestamp(new_tmsp); 
    set_timestamp_type(type);
};

/**
 * @brief Checks if the DateTime is a holiday from a list of holiday DateTimes.
 * 
 * @param holiday_datetimes A vector of shared pointers to DateTime objects representing holidays.
 * @return True if the DateTime is a holiday, false otherwise.
 */
bool DateTime::is_date_in_holiday(const std::vector<std::shared_ptr<DateTime>>& holiday_datetimes)
{
    std::unique_ptr<std::tm> time_info = get_time_info();
    for (const std::shared_ptr<DateTime>& h : holiday_datetimes) {
        std::unique_ptr<std::tm> h_time_info = h->get_time_info();
        if (time_info->tm_mday == h_time_info->tm_mday &&
            time_info->tm_mon == h_time_info->tm_mon &&
            time_info->tm_year == h_time_info->tm_year){return true;}
    }
    return false;
};

/**
 * @brief Calculates the TimeDelta between two DateTimes.
 * 
 * @param start_datetime A shared pointer to the start DateTime.
 * @param end_datetime A shared pointer to the end DateTime.
 * @param delta_type The desired timestamp type for the delta (e.g., seconds, milliseconds, etc.).
 * @return A shared pointer to the TimeDelta object representing the time difference.
 */
std::shared_ptr<TimeDelta> get_timedelta(
    const std::shared_ptr<DateTime>& start_datetime, 
    const std::shared_ptr<DateTime>& end_datetime, 
    const EpochTimestampType delta_type)
{
    EpochTimestampType start_type = start_datetime->get_timestamp_type();
    EpochTimestampType end_type = end_datetime->get_timestamp_type();

    start_datetime->convert_timestamp(delta_type); 
    end_datetime->convert_timestamp(delta_type);

    long long delta = end_datetime->get_timestamp() - start_datetime->get_timestamp(); 

    start_datetime->convert_timestamp(start_type); 
    end_datetime->convert_timestamp(end_type);

    switch(delta_type){
        case EpochTimestampType::SECONDS: 
        {
            return std::make_shared<TimeDelta>(0,0,0,delta,0,0,0);
        }
        case EpochTimestampType::MILLISECONDS: 
        {
            return std::make_shared<TimeDelta>(0,0,0,0,delta,0,0);
        }
        case EpochTimestampType::MICROSECONDS: 
        {
            return std::make_shared<TimeDelta>(0,0,0,0,0,delta,0);
        }
        case EpochTimestampType::NANOSECONDS: 
        {
            return std::make_shared<TimeDelta>(0,0,0,0,0,0,delta);
        }
    }
};

/**
 * @brief Gets the name of a day count convention.
 * 
 * @param dcc The day count convention.
 * @return The name of the day count convention.
 * @throws UndefinedDayCountConventionError If the day count convention is undefined.
 */
std::string get_day_count_convention_name(const DayCountConvention dcc)
{
    switch (dcc)
    {
    case DayCountConvention::ACT360: {return "ACT/360";}
    case DayCountConvention::ACT365: {return "ACT/365";}
    case DayCountConvention::ACT364: {return "ACT/364";}
    default: {throw UndefinedDayCountConventionError();}
    }
}; 

/**
 * @brief Gets the number of days in a year for a given day count convention.
 * 
 * @param dcc The day count convention.
 * @return The number of days in a year for the given day count convention.
 * @throws UndefinedDayCountConventionError If the day count convention is undefined.
 */
int get_number_days_in_year(const DayCountConvention dcc)
{
    switch (dcc)
    {
    case DayCountConvention::ACT360:{return 360;}
    case DayCountConvention::ACT365:{return 365;}
    case DayCountConvention::ACT364:{return 364;}
    default: {throw UndefinedDayCountConventionError();}
    }
};

/**
 * @brief Gets the number of days in a month for a given day count convention.
 * 
 * @param dcc The day count convention.
 * @return The number of days in a month for the given day count convention.
 * @throws UndefinedDayCountConventionError If the day count convention is undefined.
 */
int get_number_days_in_month(const DayCountConvention dcc)
{
    int actual_days = round(get_number_days_in_year(dcc)/12);
    switch (dcc)
    {
    case DayCountConvention::ACT360:{return actual_days;}
    case DayCountConvention::ACT365:{return actual_days;}
    case DayCountConvention::ACT364:{return actual_days;}
    default: {throw UndefinedDayCountConventionError();}
    }
}

/**
 * @brief Calculates the year fraction between two DateTimes using a given day count convention.
 * 
 * @param start_datetime The start DateTime.
 * @param end_datetime The end DateTime.
 * @param day_count_convention The day count convention to use.
 * @return The year fraction between the two DateTimes.
 * @throws NonPositiveYearFractionError If the resulting year fraction is negative.
 */
double get_year_fraction_from_datetimes(
    const std::shared_ptr<DateTime> start_datetime, 
    const std::shared_ptr<DateTime> end_datetime, 
    const DayCountConvention day_count_convention)
{
    int ns_value = static_cast<int>(EpochTimestampType::NANOSECONDS);
    std::shared_ptr<TimeDelta> dt = get_timedelta(
        start_datetime,
        end_datetime, 
        EpochTimestampType::NANOSECONDS); 
    long long total_ns = dt->get_total_nanoseconds();
    long long day_in_s = 24*60*60;
    long long day_in_ns = day_in_s*ns_value;
    double t = double(total_ns)/double(get_number_days_in_year(day_count_convention)*day_in_ns);
    if (t<0){throw NonPositiveYearFractionError();}
    return t;
};

/**
 * @brief Gets the name of a tenor.
 * 
 * @param tenor The tenor.
 * @return The name of the tenor.
 * @throws UndefinedTenorError If the tenor is undefined.
 */
std::string get_tenor_name(const Tenor tenor)
{
    switch (tenor)
    {
    case Tenor::ON:{return "ON";}
    case Tenor::TN:{return "TN";}
    case Tenor::SN:{return "SN";}
    case Tenor::_1W:{return "1W";}
    case Tenor::_2W:{return "2W";}
    case Tenor::_1M:{return "1M";}
    case Tenor::_3M:{return "3M";}
    case Tenor::_6M:{return "6M";}
    case Tenor::_1Y:{return "1Y";}
    case Tenor::_5Y:{return "5Y";}
    case Tenor::_10Y:{return "10Y";}
    case Tenor::_20Y:{return "20Y";}
    case Tenor::_30Y:{return "30Y";}
    default: {throw UndefinedTenorError();}
    }
}; 

/**
 * @brief Gets the number of days corresponding to a tenor.
 * 
 * @param tenor The tenor.
 * @param dcc The day count convention to use.
 * @return The number of days corresponding to the tenor.
 * @throws UndefinedTenorError If the tenor is undefined.
 */
int get_tenor_in_days(const Tenor tenor, const DayCountConvention dcc)
{
    int days_in_year = get_number_days_in_year(dcc); 
    int days_in_month = get_number_days_in_month(dcc); 
    switch (tenor)
    {
    case Tenor::ON:{return 1;}
    case Tenor::TN:{return 2;}
    case Tenor::SN:{return 3;}
    case Tenor::_1W:{return 7;}
    case Tenor::_2W:{return 14;}
    case Tenor::_1M:{return days_in_month;}
    case Tenor::_3M:{return 3*days_in_month;}
    case Tenor::_6M:{return 6*days_in_month;}
    case Tenor::_1Y:{return days_in_year;}
    case Tenor::_5Y:{return 5*days_in_year;}
    case Tenor::_10Y:{return 10*days_in_year;}
    case Tenor::_20Y:{return 20*days_in_year;}
    case Tenor::_30Y:{return 30*days_in_year;}
    default : {throw UndefinedTenorError();}
    }
};

/**
 * @brief Converts a tenor to a TimeDelta object.
 * 
 * @param tenor The tenor.
 * @param dcc The day count convention to use.
 * @return A shared pointer to a TimeDelta object representing the tenor.
 */
std::shared_ptr<TimeDelta> get_tenor_in_timedelta(
    const Tenor tenor, 
    const DayCountConvention dcc
)
{
    return std::make_shared<TimeDelta>(get_tenor_in_days(tenor,dcc),0,0,0,0,0,0);
};

/**
 * @brief Calculates the year fraction for a tenor using a given day count convention.
 * 
 * @param tenor The tenor.
 * @param dcc The day count convention.
 * @return The year fraction for the tenor.
 */
double get_tenor_year_fraction(const Tenor tenor, const DayCountConvention dcc)
{
    return get_tenor_in_days(tenor, dcc)/get_number_days_in_year(dcc);
};

/**
 * @brief Calculates the number of periods in a sequence based on a given frequency tenor.
 * 
 * @param start_datetime The start DateTime.
 * @param end_datetime The end DateTime.
 * @param frequency_tenor The frequency tenor.
 * @param day_count_convention The day count convention.
 * @return The number of periods in the sequence.
 */
int sequence_length_from_frequency_tenor(
    const std::shared_ptr<DateTime> start_datetime,
    const std::shared_ptr<DateTime> end_datetime,
    const Tenor frequency_tenor, 
    const DayCountConvention day_count_convention
)
{
    std::shared_ptr<TimeDelta> freq_dt = get_tenor_in_timedelta(frequency_tenor, day_count_convention); 
    std::shared_ptr<TimeDelta> dt = get_timedelta(
        start_datetime, 
        end_datetime, 
        EpochTimestampType::SECONDS
    ); 
    return round(double(dt->get_total_seconds())/double(freq_dt->get_total_seconds()));

};

/**
 * @brief Calculates the end DateTime from the start DateTime and tenor.
 * 
 * @param start_datetime The start DateTime.
 * @param end_tenor The end Tenor.
 * @param day_count_convention The day count convention to use.
 * @return A shared pointer to the end DateTime.
 */
std::shared_ptr<DateTime> get_end_datetime_from_tenor(
    const std::shared_ptr<DateTime> start_datetime,
    const Tenor end_tenor,
    const DayCountConvention day_count_convention
)
{
    std::shared_ptr<TimeDelta> dt_ptr = get_tenor_in_timedelta(end_tenor, day_count_convention); 
    std::shared_ptr<DateTime> end_datetime = std::make_shared<DateTime>(*start_datetime);
    end_datetime->apply_time_delta(dt_ptr);
    return end_datetime;
};

/**
 * @brief Orders a sequence of DateTimes in increasing order.
 * 
 * @param datetime_sequence A vector of shared pointers to DateTime objects.
 */
void order_datetime_sequence(
    std::vector<std::shared_ptr<DateTime>>& datetime_sequence
)
{
    std::set<long long> set_intervals; 
    for (const std::shared_ptr<DateTime>&  dt: datetime_sequence){
        dt->convert_timestamp(EpochTimestampType::NANOSECONDS);
        set_intervals.insert(dt->get_timestamp());
    };
    datetime_sequence.clear();
    for (long long i: set_intervals){
        datetime_sequence.push_back(std::make_unique<DateTime>(DateTime(i,EpochTimestampType::NANOSECONDS)));
    }
};

/**
 * @brief Generates a sequence of DateTimes based on a frequency tenor and day count convention.
 * 
 * @param start_datetime The start DateTime.
 * @param frequency_tenor The frequency Tenor.
 * @param day_count_convention The day count convention.
 * @param include_start Whether to include the start DateTime in the sequence.
 * @param include_end Whether to include the end DateTime in the sequence.
 * @param end_datetime The end DateTime.
 * @return A vector of shared pointers to DateTime objects.
 */
std::vector<std::shared_ptr<DateTime>> generate_datetime_sequence(
    const std::shared_ptr<DateTime> start_datetime,
    const Tenor frequency_tenor, 
    const DayCountConvention day_count_convention, 
    const bool include_start, 
    const bool include_end,
    const std::shared_ptr<DateTime> end_datetime
)
{
    std::vector<std::shared_ptr<DateTime>> output;
    std::shared_ptr<TimeDelta> dt_ptr = get_tenor_in_timedelta(frequency_tenor, day_count_convention);
    std::shared_ptr<DateTime> next_datetime = std::make_unique<DateTime>(*start_datetime);
    int n = sequence_length_from_frequency_tenor(
        start_datetime, 
        end_datetime, 
        frequency_tenor,
        day_count_convention
    );
    int i = 1;
    while (i<n){
        next_datetime->apply_time_delta(dt_ptr);
        output.push_back(std::make_shared<DateTime>(*next_datetime));
        i++;
    };
    if (include_start){
        output.insert(output.begin(), start_datetime);
    };
    if (include_end){
        output.push_back(end_datetime);
    };
    return output;
};  
