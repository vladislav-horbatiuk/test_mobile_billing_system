#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>

#include "fee_calculation/free_minutes_accounting/IFreeMinutesAccounter.hpp"

namespace MobileBillingSystem {

namespace BusinessLogic {

class HomeOperatorNetworkCallFreeMinutesAccounter : public IFreeMinutesAccounter
{
public:
    explicit HomeOperatorNetworkCallFreeMinutesAccounter(
        const boost::gregorian::days& free_minutes_valid_for_days)
        : m_free_minutes_valid_for_days{free_minutes_valid_for_days}
    {
    }

    void accountForFreeMinutes(
        CallDurationInMinutes& call_duration,
        const DataTypes::CallInfo& call_info,
        const DataTypes::SubscriberAccountInfo& caller_info) const override
    {
        if ((call_info.call_start_time.date() - caller_info.last_payment_date) >
            m_free_minutes_valid_for_days)
        {
            return;
        }
        if (caller_info.phone_number.prefix !=
            call_info.callee_phone_number.prefix)
        {
            return;
        }
        call_duration.value =
            (call_duration.value >= caller_info.free_minutes_left)
                ? (call_duration.value - caller_info.free_minutes_left)
                : 0u;
    }

private:
    const boost::gregorian::days m_free_minutes_valid_for_days;
};

} // namespace BusinessLogic

} // namespace MobileBillingSystem
