#pragma once

#include <cstddef>
#include <set>

#include <boost/fusion/include/define_struct.hpp>

#include "data_types/PhoneNumber.hpp"

/**
 * @brief structs, defined with this macro come with a few handy "extensions"
 * out-of-the-box: they can be (when certain conditions are met) automatically
 * serialized/deserialized, compared etc. So I usually tend to define structures
 * that are going to be read from/written to files using this macro.
 */
// clang-format off
BOOST_FUSION_DEFINE_STRUCT(
    (MobileBillingSystem)(ApplicationLogic), ParsablePartOfControllerConfig,
    (double, fixed_fee)
    (double, home_network_minute_price)
    (double, outside_home_network_minute_price)
    (std::size_t, free_weekend_minutes)
    (std::size_t, home_network_free_minutes_valid_for_days)
    )
// clang-format on

namespace MobileBillingSystem {

namespace ApplicationLogic {

struct ControllerConfig
{
public:
    explicit ControllerConfig(
        const std::set<DataTypes::NumberPrefix>& valid_number_prefixes,
        const ParsablePartOfControllerConfig& other_config_values)
        : valid_number_prefixes_set{valid_number_prefixes}
        , other_stuff{other_config_values}
    {
    }

    std::set<DataTypes::NumberPrefix> valid_number_prefixes_set;
    ParsablePartOfControllerConfig other_stuff;
};

class MainApplicationController
{
public:
    /**
     * @brief This method's job is to execute the single functional requirement
     * of the appliction: calculate call prices using defined calculation rules
     * @param config influences different calculation parameters
     * @param call_info_records_filename file that contains serialized call
     * info records
     * @param subscriber_accounts_info_records_filename file containing
     * serialized accounts information records
     * @param output_filename calculated prices for each call will be written
     * (simply line-by-line) in this file
     */
    static void calculateCallsPrices(
        const ControllerConfig& config,
        const std::string& call_info_records_filename,
        const std::string& subscriber_accounts_info_records_filename,
        const std::string& output_filename);
};

} // namespace ApplicationLogic

} // namespace MobileBillingSystem
