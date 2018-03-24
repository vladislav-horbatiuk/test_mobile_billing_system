#pragma once

#include "data_types/CallInfo.hpp"
#include "data_types/PhoneNumber.hpp"
#include "data_types/SubscriberAccountInfo.hpp"

namespace MobileBillingSystem {

namespace BusinessLogic {

class IDataValidator
{
public:
    virtual ~IDataValidator() = default;

    /**
     * @brief Set of validation methods.
     * @param input data type object to validate
     * @return reference to the same object
     * @throw std::runtime_error when validation fails
     */
    virtual const DataTypes::CallInfo& validate(
        const DataTypes::CallInfo& call_info) const = 0;
    virtual const DataTypes::PhoneNumber& validate(
        const DataTypes::PhoneNumber& phone_number) const = 0;
    virtual const DataTypes::SubscriberAccountInfo& validate(
        const DataTypes::SubscriberAccountInfo& acc_info) const = 0;
};

} // namespace BusinessLogic

} // namespace MobileBillingSystem
