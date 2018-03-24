#include <sstream>
#include <stdexcept>

#include "DataValidator.hpp"
#include "data_types/operators.hpp"

namespace {

const auto exceptionWithMessageAndSerializedObj =
    [](const char* err_msg, const auto& obj) {
        std::stringstream err_ss;
        err_ss << err_msg;
        err_ss << obj;
        return std::runtime_error(err_ss.str());
    };

} // anonymous namespace

namespace MobileBillingSystem {

namespace BusinessLogic {

DataValidator::DataValidator(
    const std::set<DataTypes::NumberPrefix>& allowed_number_prefixes)
    : m_allowed_number_prefixes(allowed_number_prefixes)
{
}

const DataTypes::CallInfo& DataValidator::validate(
    const DataTypes::CallInfo& call_info) const
{
    validate(call_info.callee_phone_number);
    if (call_info.call_start_time > call_info.call_end_time)
    {
        throw exceptionWithMessageAndSerializedObj(
            "Call start time > end time in call info: ", call_info);
    }
    return call_info;
}

const DataTypes::PhoneNumber& DataValidator::validate(
    const DataTypes::PhoneNumber& phone_number) const
{
    if (0 == m_allowed_number_prefixes.count(phone_number.prefix))
    {
        throw exceptionWithMessageAndSerializedObj(
            "Unknown phone number operator prefix in phone number: ",
            phone_number);
    }

    auto digits_checker = [&phone_number](const auto& digits_array) {
        for (const auto& digit : digits_array)
        {
            if ('0' > digit || '9' < digit)
            {
                throw exceptionWithMessageAndSerializedObj(
                    "Wrong digit in phone number: ", phone_number);
            }
        }
    };
    digits_checker(phone_number.prefix);
    digits_checker(phone_number.suffix);

    return phone_number;
}

const DataTypes::SubscriberAccountInfo& DataValidator::validate(
    const DataTypes::SubscriberAccountInfo& acc_info) const
{
    validate(acc_info.phone_number);
    return acc_info;
}

} // namespace BusinessLogic

} // namespace MobileBillingSystem
