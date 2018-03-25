#include <fstream>
#include <set>
#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include <gtest/gtest.h>

#include "application_controller/MainApplicationController.hpp"
#include "data_types/CallInfo.hpp"
#include "data_types/SubscriberAccountInfo.hpp"

using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace MobileBillingSystem::ApplicationLogic;
using namespace MobileBillingSystem::DataTypes;

namespace {

const PhoneNumber correct_number{{'0', '9', '3'},
                                 {'4', '3', '5', '6', '8', '9', '2'}};

const AccountId correct_id{111};
const date correct_last_payment_date{2018, Feb, 25};
const SubscriberAccountInfo correct_acc_info{correct_id,
                                             correct_number,
                                             correct_last_payment_date,
                                             3};

// 3 minutes 1 second duration call
const CallInfo correct_call_info{
    correct_id,
    correct_number,
    {date{2018, Feb, 27}, hours{10} + minutes{3} + seconds{22}},
    {date{2018, Feb, 27}, hours{10} + minutes{6} + seconds{23}}};

} // anonymous namespace

TEST(TestUtils, smoke_test_controller_validity)
{
    auto call_info_path = boost::filesystem::unique_path();
    {
        std::ofstream os(call_info_path.c_str());
        os << correct_call_info;
    }

    auto acc_info_path = boost::filesystem::unique_path();
    {
        std::ofstream os(acc_info_path.c_str());
        os << correct_acc_info;
    }

    auto output_path = boost::filesystem::unique_path();
    ParsablePartOfControllerConfig cfg_part{
        0.33, // fixed fee
        0.5,  // home network minute fee
        0.95, // outside home network minute fee
        5,    // free minutes each weekend
        30};  // how many days are home network free minutes valid after credit
    ControllerConfig full_config{{{'0', '9', '3'}}, cfg_part};

    MainApplicationController::calculateCallsPrices(
        full_config,
        call_info_path.c_str(),
        acc_info_path.c_str(),
        output_path.c_str());

    double call_price = -1.0;
    {
        std::ifstream is{output_path.c_str()};
        is >> call_price;
    }
    ASSERT_EQ(call_price, 0.83); // 0.5 * 1 + 0.33
}
