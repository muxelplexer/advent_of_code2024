#pragma once
#include <string_view>

namespace lib
{
    /// @brief converts a std::string_view into an integer.
    /// @throws std::invalid_argument - `string` can not be converted to `int`.
    int to_int(const std::string_view string);
}
