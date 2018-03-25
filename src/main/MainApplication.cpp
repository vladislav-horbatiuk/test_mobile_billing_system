#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/program_options.hpp>

#include "application_controller/MainApplicationController.hpp"
#include "utils/SimpleParser.hpp"

namespace po = boost::program_options;
using namespace MobileBillingSystem::ApplicationLogic;
using namespace MobileBillingSystem::DataTypes;
using namespace MobileBillingSystem::Utils;

namespace {

void checkPrefixDigit(char digit)
{
    if ('0' > digit || '9' < digit)
    {
        throw std::runtime_error(
            "Wrong prefix digit: " + std::to_string(digit));
    }
}
ControllerConfig parseControllerConfig(const std::string& config_path)
{
    std::ifstream is{config_path};
    skipCommentedLines(is);
    ParsablePartOfControllerConfig parsable_controller_config_part;
    is >> parsable_controller_config_part;
    skipCommentedLines(is);
    std::set<NumberPrefix> valid_number_prefixes_set;
    while (!is.eof())
    {
        char p1, p2, p3;
        is >> p1 >> p2 >> p3;
        checkPrefixDigit(p1);
        checkPrefixDigit(p2);
        checkPrefixDigit(p3);
        valid_number_prefixes_set.insert({p1, p2, p3});
        char should_be_space_or_newline;
        is >> std::noskipws >> should_be_space_or_newline;
        if (' ' != should_be_space_or_newline &&
            '\n' != should_be_space_or_newline)
        {
            throw std::runtime_error(
                "Expected space when parsing controller "
                "config valid prefixes set, got: " +
                std::string(1, should_be_space_or_newline));
        }
    }
    return ControllerConfig{valid_number_prefixes_set,
                            parsable_controller_config_part};
}

} // anonymous namespace

int main(int argc, char* argv[])
{
    std::string config_path;
    std::string call_records_path;
    std::string acc_info_records_path;
    std::string output_path;
    po::options_description desc("Test mobile billing system options");
    // clang-format off
    desc.add_options()
        ("help,h", "produce help message")
        ("controller_config,c",
         po::value<std::string>(&config_path)->required(),
         "path to controller config file")
        ("call_records_file,r",
         po::value<std::string>(&call_records_path)->required(),
         "path to file with call records")
        ("acc_info_records_file,a",
         po::value<std::string>(&acc_info_records_path)->required(),
         "path to file with account information records")
        ("output_file,o",
         po::value<std::string>(&output_path)->required(),
         "path to the output file");
    // clang-format on

    po::variables_map vm;

    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help"))
        {
            std::cout << desc << std::endl;
            return 0;
        }

        po::notify(vm);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Arguments parsing error: " << e.what() << std::endl;
        std::cerr << desc << std::endl;
        return -1;
    }

    try
    {
        auto config = parseControllerConfig(config_path);
        MainApplicationController::calculateCallsPrices(
            config, call_records_path, acc_info_records_path, output_path);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception occured: " << e.what() << std::endl;
        return -1;
    }
    catch (...)
    {
        std::cerr << "Unknown error occured." << std::endl;
        return -1;
    }
    return 0;
}
