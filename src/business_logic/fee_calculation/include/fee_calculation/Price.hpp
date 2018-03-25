#pragma once

namespace MobileBillingSystem {

namespace BusinessLogic {

struct Price
{
public:
    explicit Price(const double val)
        : value(val)
    {
    }

public:
    const double value;
};

} // namespace BusinessLogic

} // namespace MobileBillingSystem
