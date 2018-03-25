#pragma once

#include <cstddef>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "fee_calculation/IFeeCalculator.hpp"
#include "fee_calculation/Price.hpp"
#include "fee_calculation/free_minutes_accounting/IFreeMinutesAccounter.hpp"

namespace MobileBillingSystem {

namespace BusinessLogic {

class DurationBasedFeeCalculator : public IFeeCalculator
{
public:
    explicit DurationBasedFeeCalculator(
        const Price& home_network_minute_price,
        const Price& outside_home_network_minute_price,
        const IFreeMinutesAccounter& free_minutes_accounter)
        : m_free_minutes_accounter{free_minutes_accounter}
        , m_home_network_minute_price{home_network_minute_price}
        , m_outside_home_network_minute_price{outside_home_network_minute_price}
    {
    }

    double calculateFee(
        const DataTypes::CallInfo& call_info,
        const DataTypes::SubscriberAccountInfo& caller_info) const override
    {
        auto total_call_seconds =
            (call_info.call_end_time - call_info.call_start_time)
                .total_seconds();
        auto total_minutes = total_call_seconds / 60;
        if (0 != total_call_seconds % 60)
        {
            total_minutes++;
        }
        CallDurationInMinutes call_duration{
            static_cast<std::size_t>(total_minutes)};
        m_free_minutes_accounter.accountForFreeMinutes(
            call_duration, call_info, caller_info);
        double minute_price = (call_info.callee_phone_number.prefix ==
                               caller_info.phone_number.prefix)
                                  ? m_home_network_minute_price.value
                                  : m_outside_home_network_minute_price.value;
        return call_duration.value * minute_price;
    }

private:
    const IFreeMinutesAccounter& m_free_minutes_accounter;
    const Price m_home_network_minute_price;
    const Price m_outside_home_network_minute_price;
};

} // namespace BusinessLogic

} // namespace MobileBillingSystem
