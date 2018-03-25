#include "application_controller/MainApplicationController.hpp"

#include <fstream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>

#include <boost/date_time/gregorian/gregorian.hpp>

#include "data_types/SubscriberAccountInfo.hpp"
#include "data_validation/DataValidatorFactory.hpp"
#include "data_validation/IDataValidator.hpp"
#include "fee_calculation/DurationBasedFeeCalculator.hpp"
#include "fee_calculation/FeeCalculatorComposite.hpp"
#include "fee_calculation/FixedFeeCalculator.hpp"
#include "fee_calculation/IFeeCalculator.hpp"
#include "fee_calculation/free_minutes_accounting/FreeMinutesAccounterComposite.hpp"
#include "fee_calculation/free_minutes_accounting/HomeOperatorNetworkCallFreeMinutesAccounter.hpp"
#include "fee_calculation/free_minutes_accounting/IFreeMinutesAccounter.hpp"
#include "fee_calculation/free_minutes_accounting/WeekendFreeMinutesAccounter.hpp"
#include "utils/SimpleParser.hpp"

using namespace MobileBillingSystem::DataTypes;
using namespace MobileBillingSystem::BusinessLogic;
using namespace boost::gregorian;

namespace MobileBillingSystem {

namespace ApplicationLogic {

void MainApplicationController::calculateCallsPrices(
    const ControllerConfig& config,
    const std::string& call_info_records_filename,
    const std::string& subscriber_accounts_info_records_filename,
    const std::string& output_filename)
{
    std::unique_ptr<IDataValidator> validator =
        DataValidatorFactory::createValidator(config.valid_number_prefixes_set);

    std::map<AccountId, SubscriberAccountInfo> accounts_info_map;
    auto accounts_parsing_functor = [&accounts_info_map, &validator](
        const SubscriberAccountInfo& acc_info) {
        accounts_info_map[acc_info.account_id] = validator->validate(acc_info);
    };

    Utils::parseFileApplyingFunctor<SubscriberAccountInfo>(
        subscriber_accounts_info_records_filename, accounts_parsing_functor);

    WeekendFreeMinutesAccounter weekends_free_minutes_acc{
        CallDurationInMinutes{config.other_stuff.free_weekend_minutes}};
    days home_network_free_minutes_validity_duration{static_cast<long int>(
        config.other_stuff.home_network_free_minutes_valid_for_days)};
    HomeOperatorNetworkCallFreeMinutesAccounter home_network_free_minutes_acc{
        home_network_free_minutes_validity_duration};
    FreeMinutesAccounterComposite composite_acc{weekends_free_minutes_acc,
                                                home_network_free_minutes_acc};

    FixedFeeCalculator fixed_fee_calc{Price{config.other_stuff.fixed_fee}};
    DurationBasedFeeCalculator duration_based_fee_calc{
        Price{config.other_stuff.home_network_minute_price},
        Price{config.other_stuff.outside_home_network_minute_price},
        composite_acc};
    FeeCalculatorComposite final_fee_calc{fixed_fee_calc,
                                          duration_based_fee_calc};

    std::ofstream os{output_filename};
    auto call_info_parsing_functor =
        [&accounts_info_map, &validator, &final_fee_calc, &os](
            const CallInfo& call_info) {
            const CallInfo& info = validator->validate(call_info);
            auto acc_info_it = accounts_info_map.find(info.caller_account_id);
            if (accounts_info_map.end() == acc_info_it)
            {
                std::stringstream err_ss;
                err_ss << "Unknown account id in call info: ";
                err_ss << call_info;
                throw std::runtime_error(err_ss.str());
            }
            os << final_fee_calc.calculateFee(info, acc_info_it->second);
        };
    Utils::parseFileApplyingFunctor<CallInfo>(
        call_info_records_filename, call_info_parsing_functor);
}

} // namespace ApplicationLogic

} // namespace MobileBillingSystem
