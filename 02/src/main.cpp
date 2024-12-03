#include "conversion.hpp"
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <cstdint>
#include <exception>
#include <iostream>
#include <range/v3/algorithm/is_sorted.hpp>
#include <range/v3/functional/comparisons.hpp>
#include <string>
#include <print>
#include <string_view>
#include <vector>

#include <range/v3/range.hpp>
#include <range/v3/algorithm.hpp>
using level = uint8_t;

struct report
{
    bool is_safe() const;
    std::vector<level> levels;
};

template<>
struct fmt::formatter<report>
{
    template<class ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template<class FormatContext>
    auto format(const report& rep, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "{}", fmt::join(rep.levels, " "));
    }
};

std::vector<report> parse_input(const std::span<std::string> input);

int main() try
{
    std::vector<std::string> lines;
    lines.reserve(1000);
    for (std::string line; std::getline(std::cin, line); )
    {
        lines.emplace_back(std::move(line));
    }
    auto reports{parse_input(lines)};

    struct {
        int safe{0};
        int unsafe{0};
    } inputs;
    for (const auto& rep : reports)
    {
        if (rep.is_safe())
        {
            ++inputs.safe;
            fmt::println("Safe input: {}", rep);
        }
        else
        {
            ++inputs.unsafe;
            fmt::println("Unsafe input: {}", rep);
        }
    }
    fmt::println("Safe: {} || Unsafe: {}", inputs.safe, inputs.unsafe);
} catch(const std::exception& ex)
{
    fmt::println("ERROR: {}", ex.what());
    return 1;
}

std::vector<report> parse_input(const std::span<std::string> input)
{
    std::vector<report> reports{};
    reports.reserve(1000);
    for (const auto& line : input)
    {
        if (line.empty()) continue;
        fmt::println("{}", line);

        report rep{};
        rep.levels.reserve(8);

        size_t last_pos{0};
        bool parsing = true;
        while (parsing)
        {
            const auto start_pos{std::cbegin(line) + last_pos};
            const auto delim_pos{line.find_first_of(' ', last_pos)};
            const auto end_pos{delim_pos != line.npos ?
                            std::cbegin(line) + delim_pos :
                            std::cend(line)
            };
            const std::string_view number{
                start_pos,
                end_pos
            };
            rep.levels.emplace_back(lib::to_int(number));
            if (end_pos == std::cend(line)) parsing = false;

            last_pos = delim_pos + 1;
        }
        reports.emplace_back(rep);
    }
    return reports;
}

bool report::is_safe() const
{
    const bool correct_sorting{
        ranges::is_sorted(this->levels, ranges::less{}) ||
        ranges::is_sorted(this->levels, ranges::greater{})
    };
    if (!correct_sorting) return correct_sorting;

    const uint8_t* last_level{nullptr};
    for (const auto& level : this->levels)
    {
        if (!last_level)
        {
            last_level = &level;
            continue;
        }
        const auto delta{std::abs(*last_level - level)};
        if (delta < 1 || delta > 3) return false;
        last_level = &level;
    }
    return true;
}
