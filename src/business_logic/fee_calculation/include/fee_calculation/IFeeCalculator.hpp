#pragma once

#include "data_types/CallInfo.hpp"
#include "data_types/SubscriberAccountInfo.hpp"

namespace MobileBillingSystem {

namespace BusinessLogic {

class IFeeCalculator
{
public:
    virtual ~IFeeCalculator() = default;

    virtual double calculateFee(
        const DataTypes::CallInfo& call_info,
        const DataTypes::SubscriberAccountInfo& caller_info) const = 0;
};

} // namespace BusinessLogic

} // namespace MobileBillingSystem
