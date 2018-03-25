#pragma once

#include <cstddef>
#include <string>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/fusion/include/define_struct.hpp>

#include "data_types/PhoneNumber.hpp"
#include "data_types/operators.hpp"

namespace MobileBillingSystem {

namespace DataTypes {

using AccountId = std::size_t;

} // namespace DataTypes

} // namespace MobileBillingSystem

// clang-format off
BOOST_FUSION_DEFINE_STRUCT(
    (MobileBillingSystem)(DataTypes), SubscriberAccountInfo,
    (MobileBillingSystem::DataTypes::AccountId, account_id)
    (MobileBillingSystem::DataTypes::PhoneNumber, phone_number)
    (boost::gregorian::date, last_payment_date)
    (std::size_t, free_minutes_left)
    )
// clang-format on
