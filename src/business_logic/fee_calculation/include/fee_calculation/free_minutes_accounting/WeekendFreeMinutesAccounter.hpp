#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>

#include "fee_calculation/free_minutes_accounting/IFreeMinutesAccounter.hpp"

namespace MobileBillingSystem {

namespace BusinessLogic {

class WeekendFreeMinutesAccounter : public IFreeMinutesAccounter
{
public:
    explicit WeekendFreeMinutesAccounter(
        const CallDurationInMinutes& free_weekend_minutes)
        : m_free_weekend_minutes{free_weekend_minutes}
    {
    }

    void accountForFreeMinutes(
        CallDurationInMinutes& call_duration,
        const DataTypes::CallInfo& call_info,
        const DataTypes::SubscriberAccountInfo& caller_info) const override
    {
        auto call_day_of_week = call_info.call_start_time.date().day_of_week();
        if (call_day_of_week == boost::date_time::Saturday ||
            call_day_of_week == boost::date_time::Sunday)
        {
            call_duration.value =
                (call_duration.value >= m_free_weekend_minutes.value)
                    ? (call_duration.value - m_free_weekend_minutes.value)
                    : 0u;
        }
    }

private:
    const CallDurationInMinutes m_free_weekend_minutes;
};

} // namespace BusinessLogic

} // namespace MobileBillingSystem
