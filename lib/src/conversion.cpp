#include "conversion.hpp"
#include <charconv>
#include <format>
#include <stdexcept>
#include <system_error>

namespace lib
{
    int to_int(const std::string_view string)
    {
        int num;
        const auto num_res{std::from_chars(string.data(), string.data() + string.size(), num)};
        if (num_res.ec == std::errc::invalid_argument)
        {
            throw std::invalid_argument(std::format("to_int: input '{}' can not be converted to a number", string));
        }
        return num;
    }
}
