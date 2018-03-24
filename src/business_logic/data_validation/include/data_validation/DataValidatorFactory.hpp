#pragma once

#include <memory>
#include <set>

#include "data_types/PhoneNumber.hpp"
#include "data_validation/IDataValidator.hpp"

namespace MobileBillingSystem {

namespace BusinessLogic {

class DataValidatorFactory
{
public:
    static std::unique_ptr<IDataValidator> createValidator(
        const std::set<DataTypes::NumberPrefix>& allowed_number_prefixes);
};

} // namespace BusinessLogic

} // namespace MobileBillingSystem
