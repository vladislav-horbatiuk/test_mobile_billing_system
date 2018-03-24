#pragma once

#include <set>

#include "data_types/PhoneNumber.hpp"
#include "data_validation/IDataValidator.hpp"

namespace MobileBillingSystem {

namespace BusinessLogic {

class DataValidator : public IDataValidator
{
public:
    explicit DataValidator(
        const std::set<DataTypes::NumberPrefix>& allowed_number_prefixes);

    const DataTypes::CallInfo& validate(
        const DataTypes::CallInfo& call_info) const override;
    const DataTypes::PhoneNumber& validate(
        const DataTypes::PhoneNumber& phone_number) const override;
    const DataTypes::SubscriberAccountInfo& validate(
        const DataTypes::SubscriberAccountInfo& acc_info) const override;

private:
    const std::set<DataTypes::NumberPrefix> m_allowed_number_prefixes;
};

} // namespace BusinessLogic

} // namespace MobileBillingSystem
