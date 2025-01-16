#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <set>

enum EpochTimestampType 
{
    SECONDS = 1, 
    MILLISECONDS = 1000, 
    MICROSECONDS = 1000000, 
    NANOSECONDS = 1000000000 
};

enum Tenor
{
    ON, TN, SN, 
    _1W, _2W, 
    _1M, _3M, _6M, 
    _1Y, _5Y, _10Y, _20Y, _30Y

};

enum DayCountConvention {ACT360, ACT365, ACT364};

class NegativeEpochTimestampError: public std::exception 
{public: const char * what() const throw();};

class UndefinedDayCountConventionError : public std::exception 
{public: const char * what() const throw();};

class UndefinedTenorError : public std::exception 
{public: const char * what() const throw();};

class NonPositiveYearFractionError : public std::exception 
{public: const char * what() const throw();};

class TimeDelta
{
    public:
        TimeDelta(
            long long days, 
            long long hours, 
            long long minutes, 
            long long seconds, 
            long long milliseconds, 
            long long microseconds, 
            long long nanoseconds);
        ~TimeDelta(){};
        long long get_total_seconds();
        long long get_total_milliseconds();
        long long get_total_microseconds();
        long long get_total_nanoseconds();
        void set_days(const long long n); 
        void set_hours(const long long n); 
        void set_minutes(const long long n); 
        void set_seconds(const long long n); 
        void set_milliseconds(const long long n); 
        void set_microseconds(const long long n); 
        void set_nanoseconds(const long long n); 
    private:
        long long d; 
        long long h; 
        long long m; 
        long long s; 
        long long ms; 
        long long mcs;
        long long ns;

}; 

class DateTime
{
    public:
        DateTime(long long timestamp, EpochTimestampType type);
        ~DateTime(){};
        long long get_timestamp(); 
        EpochTimestampType get_timestamp_type();
        void set_timestamp(const long long timestamp); 
        void set_timestamp_type(const EpochTimestampType type); 
        void convert_timestamp(const EpochTimestampType type);
        void apply_time_delta(const std::shared_ptr<TimeDelta> dt);
        bool is_week_end();
        bool is_date_in_holiday(const std::vector<std::shared_ptr<DateTime>>& holiday_datetimes);
        std::unique_ptr<std::tm> get_time_info();
    private:
        long long tmsp; 
        EpochTimestampType type_; 
};

std::shared_ptr<TimeDelta> get_timedelta(
    const std::shared_ptr<DateTime>& start_datetime, 
    const std::shared_ptr<DateTime>& end_datetime, 
    const EpochTimestampType delta_type);

std::string get_day_count_convention_name(const DayCountConvention dcc); 

int get_number_days_in_year(const DayCountConvention dcc); 

int get_number_days_in_month(const DayCountConvention dcc); 

double get_year_fraction_from_datetimes(
    const std::shared_ptr<DateTime> start_datetime, 
    const std::shared_ptr<DateTime> end_datetime, 
    const DayCountConvention convention
); 

std::string get_tenor_name(const Tenor tenor); 

int get_tenor_in_days(const Tenor tenor, const DayCountConvention dcc);

std::shared_ptr<TimeDelta> get_tenor_in_timedelta(
    const Tenor tenor, 
    const DayCountConvention dcc
);

double get_tenor_year_fraction(const Tenor tenor, const DayCountConvention dcc); 

int sequence_length_from_frequency_tenor(
    const std::shared_ptr<DateTime> start_datetime,
    const std::shared_ptr<DateTime> end_datetime,
    const Tenor frequency_tenor, 
    const DayCountConvention day_count_convention
);

std::shared_ptr<DateTime> get_end_datetime_from_tenor(
    const std::shared_ptr<DateTime> start_datetime,
    const Tenor end_tenor,
    const DayCountConvention day_count_convention
);

void order_datetime_sequence(
    std::vector<std::shared_ptr<DateTime>>& datetime_sequence
);

std::vector<std::shared_ptr<DateTime>> generate_datetime_sequence(
    const std::shared_ptr<DateTime> start_datetime,
    const Tenor frequency_tenor, 
    const DayCountConvention day_count_convention, 
    const bool include_start, 
    const bool include_end,
    const std::shared_ptr<DateTime> end_datetime
);



