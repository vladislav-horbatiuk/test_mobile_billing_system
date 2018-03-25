#pragma once

#include <cstddef>

#include "data_types/CallInfo.hpp"
#include "data_types/SubscriberAccountInfo.hpp"

namespace MobileBillingSystem {

namespace BusinessLogic {

struct CallDurationInMinutes
{
public:
    explicit CallDurationInMinutes(const std::size_t& val)
        : value{val}
    {
    }

public:
    std::size_t value;
};

class IFreeMinutesAccounter
{
public:
    virtual ~IFreeMinutesAccounter() = default;

    virtual void accountForFreeMinutes(
        CallDurationInMinutes& call_duration,
        const DataTypes::CallInfo& call_info,
        const DataTypes::SubscriberAccountInfo& caller_info) const = 0;
};

} // namespace BusinessLogic

} // namespace MobileBillingSystem
