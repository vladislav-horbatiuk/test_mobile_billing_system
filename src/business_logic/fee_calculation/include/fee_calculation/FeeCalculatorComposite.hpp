#pragma once

#include "fee_calculation/IFeeCalculator.hpp"

namespace MobileBillingSystem {

namespace BusinessLogic {

class FeeCalculatorComposite : public IFeeCalculator
{
public:
    /**
     * @brief Composite fee calculator - simply sums up all fees from composed
     * calculators
     * @tparam TCalculators composed calculators' types
     * @param calculators composed calculators' objects - they are not owned
     * by this object, it is your job to correctly manage their lifetime
     */
    template <class... TCalculators>
    explicit FeeCalculatorComposite(TCalculators&&... calculators)
    {
        m_actual_calculator = [&](
            const DataTypes::CallInfo& call_info,
            const DataTypes::SubscriberAccountInfo& caller_info) {
            return (... + calculators.calculateFee(call_info, caller_info));
        };
    }

    double calculateFee(
        const DataTypes::CallInfo& call_info,
        const DataTypes::SubscriberAccountInfo& caller_info) const override
    {
        return m_actual_calculator(call_info, caller_info);
    }

private:
    using ActualCalculatorFn = std::function<double(
        const DataTypes::CallInfo&,
        const DataTypes::SubscriberAccountInfo&)>;

private:
    ActualCalculatorFn m_actual_calculator;
};

} // namespace BusinessLogic

} // namespace MobileBillingSystem
