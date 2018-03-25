#include <cstdio>
#include <fstream>
#include <vector>

#include <gtest/gtest.h>

#include "utils/SimpleParser.hpp"

TEST(TestUtils, basic_logic_works_correctly_test)
{
    auto tmp_filename = std::tmpnam(nullptr);

    std::vector<int> vec;
    for (int i = 0; i < 100; ++i)
    {
        vec.push_back(i);
    }

    {
        std::ofstream os(tmp_filename);
        for (const auto& i : vec)
        {
            os << i << std::endl;
        }
    }
    int i = 0;
    auto functor = [i, &vec](const int& val) mutable {
        ASSERT_EQ(vec[i], val);
        i++;
    };
    MobileBillingSystem::Utils::parseFileApplyingFunctor<int>(
        tmp_filename, functor);
}
