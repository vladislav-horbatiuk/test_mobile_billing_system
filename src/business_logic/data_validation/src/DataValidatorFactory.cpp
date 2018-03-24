#include "data_validation/DataValidatorFactory.hpp"

#include <memory>

#include "DataValidator.hpp"

namespace MobileBillingSystem {

namespace BusinessLogic {

std::unique_ptr<IDataValidator> DataValidatorFactory::createValidator(
    const std::set<DataTypes::NumberPrefix>& allowed_number_prefixes)
{
    return std::make_unique<DataValidator>(allowed_number_prefixes);
}

} // namespace BusinessLogic

} // namespace MobileBillingSystem
