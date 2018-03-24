#pragma once

#include <boost/fusion/include/comparison.hpp>
#include <boost/fusion/include/io.hpp>

namespace MobileBillingSystem {

namespace DataTypes {

using boost::fusion::operator<<;
using boost::fusion::operator>>;
using boost::fusion::operator==;

} // namespace DataTypes

} // namespace MobileBillingSystem
