#include <exception>
#include <sstream>
#include <string>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

#include "data_types/CallInfo.hpp"
#include "data_types/PhoneNumber.hpp"
#include "data_types/SubscriberAccountInfo.hpp"

using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace MobileBillingSystem::DataTypes;

namespace {

const PhoneNumber expected_number{{'0', '9', '3'},
                                  {'4', '3', '5', '6', '8', '9', '2'}};
const std::string expected_number_str{"0934356892"};

const AccountId expected_id{111};
const date expected_date{2018, Feb, 25};
const SubscriberAccountInfo expected_acc_info{expected_id,
                                              expected_number,
                                              expected_date};
// account_info_str == "(111 0934356892 2018-Feb-25)"
const std::string expected_account_info_str{"(111 " + expected_number_str +
                                            " 2018-Feb-25)"};

const CallInfo expected_call_info{
    expected_id,
    expected_number,
    {expected_date, hours{10} + minutes{3} + seconds{22}},
    {expected_date, hours{10} + minutes{7} + seconds{2}}};
const std::string expected_call_info_str{
    "(111 " + expected_number_str +
    " 2018-Feb-25 10:03:22 2018-Feb-25 10:07:02)"};

} // anonymous namespace

TEST(TestDataTypesSerialization, phone_number_deserialize)
{
    std::stringstream ss{expected_number_str};
    ss.exceptions(std::ios::failbit);
    PhoneNumber actual_number;
    ss >> actual_number;
    ASSERT_EQ(actual_number, expected_number);
}

TEST(TestDataTypesSerialization, phone_number_serialize)
{
    std::stringstream ss;
    ss.exceptions(std::ios::failbit);
    ss << expected_number;
    ASSERT_EQ(ss.str(), expected_number_str);
}

TEST(TestDataTypesSerialization, subscriber_account_info_deserialize)
{
    std::stringstream ss{expected_account_info_str};
    ss.exceptions(std::ios::failbit);
    SubscriberAccountInfo actual_acc_info;
    ss >> actual_acc_info;
    ASSERT_EQ(actual_acc_info, expected_acc_info);
}

TEST(TestDataTypesSerialization, subscriber_account_info_serialize)
{
    std::stringstream ss;
    ss.exceptions(std::ios::failbit);
    ss << expected_acc_info;
    ASSERT_EQ(ss.str(), expected_account_info_str);
}

TEST(TestDataTypesSerialization, call_info_deserialize)
{
    std::stringstream ss{expected_call_info_str};
    ss.exceptions(std::ios::failbit);
    CallInfo actual_call_info;
    ss >> actual_call_info;
    ASSERT_EQ(actual_call_info, expected_call_info);
}

TEST(TestDataTypesSerialization, call_info_serialize)
{
    std::stringstream ss;
    ss.exceptions(std::ios::failbit);
    ss << expected_call_info;
    ASSERT_EQ(ss.str(), expected_call_info_str);
}

TEST(TestDataTypesSerialization, subscriber_account_info_deserialize_throw)
{
    std::string bad_acc_info_str = "(111 0931a231 2018-Feb-25)";
    std::stringstream ss(bad_acc_info_str);
    ss.exceptions(std::ios::failbit);
    SubscriberAccountInfo acc_info;
    ASSERT_THROW(ss >> acc_info, std::exception);
}
