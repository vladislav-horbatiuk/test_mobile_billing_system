#pragma once

#include <algorithm>
#include <array>
#include <istream>
#include <iterator>
#include <ostream>

#include <boost/fusion/include/define_struct.hpp>

#include "data_types/operators.hpp"

namespace MobileBillingSystem {

namespace DataTypes {

using NumberPrefix = std::array<char, 3>;
using NumberSuffix = std::array<char, 7>;

} // namespace DataTypes

} // namespace MobileBillingSystem

// clang-format off
BOOST_FUSION_DEFINE_STRUCT(
    (MobileBillingSystem)(DataTypes), PhoneNumber,
    (MobileBillingSystem::DataTypes::NumberPrefix, prefix)
    (MobileBillingSystem::DataTypes::NumberSuffix, suffix)
    )
// clang-format on

namespace MobileBillingSystem {

namespace DataTypes {

inline std::ostream& operator<<(
    std::ostream& os,
    const MobileBillingSystem::DataTypes::PhoneNumber& number)
{
    std::copy(
        number.prefix.cbegin(),
        number.prefix.cend(),
        std::ostream_iterator<char>(os, ""));
    std::copy(
        number.suffix.cbegin(),
        number.suffix.cend(),
        std::ostream_iterator<char>(os, ""));
    return os;
}

inline std::istream& operator>>(
    std::istream& is,
    MobileBillingSystem::DataTypes::PhoneNumber& number)
{
    std::istream::sentry sentry{is, true};
    if (!sentry)
    {
        return is;
    }

    auto read_digit_and_perform_checks = [&is](char& digit_to_set) -> bool {
        std::istream::sentry sentry{is, true};
        if (!sentry)
        {
            is.setstate(std::ios_base::failbit);
            return false;
        }

        char digit_candidate;
        is >> digit_candidate;
        if ('9' < digit_candidate || '0' > digit_candidate)
        {
            is.setstate(std::ios_base::failbit);
            return false;
        }
        digit_to_set = digit_candidate;
        return true;
    };

    for (auto& prefix_digit : number.prefix)
    {
        if (!read_digit_and_perform_checks(prefix_digit))
        {
            return is;
        }
    }

    for (auto& suffix_digit : number.suffix)
    {
        if (!read_digit_and_perform_checks(suffix_digit))
        {
            return is;
        }
    }

    return is;
}

} // namespace operators

} // namespace fusion
