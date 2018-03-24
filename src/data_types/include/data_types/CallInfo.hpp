#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/fusion/include/define_struct.hpp>

#include "data_types/PhoneNumber.hpp"
#include "data_types/SubscriberAccountInfo.hpp"
#include "data_types/operators.hpp"

// clang-format off
BOOST_FUSION_DEFINE_STRUCT(
    (MobileBillingSystem)(DataTypes), CallInfo,
    (MobileBillingSystem::DataTypes::AccountId, caller_account_id)
    (MobileBillingSystem::DataTypes::PhoneNumber, callee_phone_number)
    (boost::posix_time::ptime, call_start_time)
    (boost::posix_time::ptime, call_end_time)
    )
// clang-format on
