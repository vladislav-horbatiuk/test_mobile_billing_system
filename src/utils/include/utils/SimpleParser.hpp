#pragma once

#include <fstream>
#include <string>

namespace MobileBillingSystem {

namespace Utils {

/**
 * @brief Parse file by iteratively streaming its contents into some object and
 * calling passed in functor on the resulting object, until EOF is reached.
 * @tparam T type of objects that are serialized in the file
 * @tparam TFunctor type of functor to be executed on each deserialized object
 * @param file_path path to the file with serialized objects
 * @param functor functor object
 */
template <class T, class TFunctor>
void parseFileApplyingFunctor(const std::string& file_path, TFunctor&& functor)
{
    std::ifstream is(file_path);
    if (!is.is_open())
    {
        throw std::runtime_error("Failed to open file at path: " + file_path);
    }
    T val;
    while (is >> val)
    {
        functor(val);
    }
}

} // namespace Utils

} // namespace MobileBillingSystem
