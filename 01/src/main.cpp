#include <charconv>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <range/v3/view/zip.hpp>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>
#include <range/v3/view.hpp>
#include <range/v3/action/sort.hpp>

using ranges::views::zip;

std::pair<std::vector<int>, std::vector<int>> parse_lines();
int solve_first_star(const auto zip_view);

int main() {
    const auto [first, second]{parse_lines()};
    const auto zipped_view{zip(first, second)};

    // star 1
    const auto delta_sum{solve_first_star(zipped_view)};
    std::cout << delta_sum << "\n";

    // star 2

    return 0;
}

std::pair<std::vector<int>, std::vector<int>> parse_lines()
{
    std::vector<int> first;
    std::vector<int> second;
    first.reserve(1000);
    second.reserve(1000);
    for (std::string line; std::getline(std::cin, line); )
    {
        const auto delim{line.find_first_of(' ')};
        if (delim == line.npos)
        {
            throw std::invalid_argument("invalid format");
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
            throw std::invalid_argument("invalid format");
        }

        const auto sres{std::from_chars(second_str.data(), second_str.data() + second_str.size(), sint)};
        if (sres.ec == std::errc::invalid_argument)
        {
            throw std::invalid_argument("invalid format");
        }

        first.emplace_back(fint);
        second.emplace_back(sint);
    }

    first |= ranges::actions::sort;
    second |= ranges::actions::sort;
    return std::make_pair(first, second);
}

int solve_first_star(const auto zip_view)
{
    auto delta_sum{0};
    for (const auto& [f, s] : zip_view)
    {
        const auto delta{std::abs(f - s)};
        delta_sum += delta;
    }
    return delta_sum;
}
