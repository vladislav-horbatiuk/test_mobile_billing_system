#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

#include "data_validation/DataValidatorFactory.hpp"

using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace MobileBillingSystem::BusinessLogic;
using namespace MobileBillingSystem::DataTypes;

namespace {

const PhoneNumber correct_number{{'0', '9', '3'},
                                 {'4', '3', '5', '6', '8', '9', '2'}};

const AccountId correct_id{111};
const date correct_last_payment_date{2018, Feb, 25};
const SubscriberAccountInfo correct_acc_info{correct_id,
                                             correct_number,
                                             correct_last_payment_date};

const CallInfo correct_call_info{
    correct_id,
    correct_number,
    {correct_last_payment_date, hours{10} + minutes{3} + seconds{22}},
    {correct_last_payment_date, hours{10} + minutes{7} + seconds{2}}};

const std::unique_ptr<IDataValidator> validator =
    DataValidatorFactory::createValidator({correct_number.prefix});

} // anonymous namespace

TEST(TestDataValidation, validation_successful_for_correct_data)
{
    const auto& number = validator->validate(correct_number);
    ASSERT_EQ(&number, &correct_number);
    const auto& call_info = validator->validate(correct_call_info);
    ASSERT_EQ(&call_info, &correct_call_info);
    const auto& acc_info = validator->validate(correct_acc_info);
    ASSERT_EQ(&acc_info, &correct_acc_info);
}

TEST(TestDataValidation, validation_throws_on_wrong_number_prefix)
{
    PhoneNumber number_with_wrong_prefix = correct_number;
    number_with_wrong_prefix.prefix = {'1', '1', '1'};
    ASSERT_THROW(
        validator->validate(number_with_wrong_prefix), std::runtime_error);
}

TEST(TestDataValidation, validation_throws_on_wrong_number)
{
    PhoneNumber wrong_number = correct_number;
    wrong_number.suffix[2] = 'A';
    ASSERT_THROW(validator->validate(wrong_number), std::runtime_error);
}

TEST(TestDataValidation, validation_throws_on_wrong_call_times)
{
    CallInfo call_info_with_wrong_times = correct_call_info;
    std::swap(
        call_info_with_wrong_times.call_start_time,
        call_info_with_wrong_times.call_end_time);
    ASSERT_THROW(
        validator->validate(call_info_with_wrong_times), std::runtime_error);
}
