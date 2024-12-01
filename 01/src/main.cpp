#include <charconv>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <ranges>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>
#include <range/v3/view.hpp>
#include <range/v3/action/sort.hpp>

namespace views = std::ranges::views;

int main()
{
    int i = 0;
    std::vector<int> first;
    std::vector<int> second;

    first.reserve(1000);
    second.reserve(1000);
    for (std::string line; std::getline(std::cin, line); i++)
    {
        const auto delim{line.find_first_of(' ')};
        if (delim == line.npos)
        {
            return 1;
        }

        const std::string_view first_str{
            std::cbegin(line), 
            std::cbegin(line) + delim
        };

        const std::string_view second_str{
            std::cbegin(line) + delim + 3,
            std::cend(line)
        };
        int fint;
        int sint;
        const auto fres{std::from_chars(first_str.data(), first_str.data() + first_str.size(), fint)};
        if (fres.ec == std::errc::invalid_argument)
        {
            return 1;
        }

        const auto sres{std::from_chars(second_str.data(), second_str.data() + second_str.size(), sint)};
        if (sres.ec == std::errc::invalid_argument)
        {
            return 1;
        }
        first.emplace_back(fint);
        second.emplace_back(sint);
    }
    first |= ranges::actions::sort;
    second |= ranges::actions::sort;

    const auto test{views::zip(
            first,
            second
    )};
    auto delta_sum{0};
    for (const auto& [f, s] : test)
    {
        auto delta{std::abs(f - s)};
        std::cout << delta << " " << f << " " << s << "\n";
        delta_sum += delta;
    }
    std::cout << delta_sum << "\n";
    return 0;
}

