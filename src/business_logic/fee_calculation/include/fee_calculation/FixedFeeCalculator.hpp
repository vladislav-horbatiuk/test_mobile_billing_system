#pragma once

#include "fee_calculation/IFeeCalculator.hpp"
#include "fee_calculation/Price.hpp"

namespace MobileBillingSystem {

namespace BusinessLogic {

class FixedFeeCalculator : public IFeeCalculator
{
public:
    explicit FixedFeeCalculator(const Price& fixed_fee)
        : m_fixed_fee{fixed_fee}
    {
    }

    double calculateFee(
        const DataTypes::CallInfo& call_info,
        const DataTypes::SubscriberAccountInfo& caller_info) const override
    {
        return m_fixed_fee.value;
    }

private:
    const Price m_fixed_fee;
};

} // namespace BusinessLogic

} // namespace MobileBillingSystem
