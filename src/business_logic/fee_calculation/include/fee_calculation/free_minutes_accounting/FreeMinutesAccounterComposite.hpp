#pragma once

#include <functional>

#include "fee_calculation/free_minutes_accounting/IFreeMinutesAccounter.hpp"

namespace MobileBillingSystem {

namespace BusinessLogic {

class FreeMinutesAccounterComposite : public IFreeMinutesAccounter
{
public:
    /**
     * @brief Composite free minutes accounter - simply executes every
     * composed accounter in order
     * @tparam TFreeMinutesAccounters type of composed accounters'
     * @param accounters composed accounters' objects; they won't be owned,
     * it is your job to correctly manage their lifetime
     */
    template <class... TFreeMinutesAccounters>
    explicit FreeMinutesAccounterComposite(
        TFreeMinutesAccounters&&... accounters)
    {
        m_actual_accounter = [&](
            CallDurationInMinutes& call_duration,
            const DataTypes::CallInfo& call_info,
            const DataTypes::SubscriberAccountInfo& caller_info) {
            int dummy[] = {
                (accounters.accountForFreeMinutes(
                     call_duration, call_info, caller_info),
                 0)...};
        };
    }

    void accountForFreeMinutes(
        CallDurationInMinutes& call_duration,
        const DataTypes::CallInfo& call_info,
        const DataTypes::SubscriberAccountInfo& caller_info) const override
    {
        m_actual_accounter(call_duration, call_info, caller_info);
    }

private:
    using ActualAccounterFn = std::function<void(
        CallDurationInMinutes&,
        const DataTypes::CallInfo&,
        const DataTypes::SubscriberAccountInfo&)>;

private:
    ActualAccounterFn m_actual_accounter;
};

} // namespace BusinessLogic

} // namespace MobileBillingSystem
