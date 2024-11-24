//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++ (supporting code)
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT

#include "doctest_compatibility.h"

#include <string>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>
using nlohmann::json;

TEST_CASE_TEMPLATE("checking forward-iterators 2", T, // NOLINT(readability-math-missing-parentheses)
                   std::vector<int>, std::string, nlohmann::json)
{
    auto it1 = typename T::iterator{};
    auto it2 = typename T::iterator{};
    CHECK(it1 == it2);
    CHECK(it1 <= it2);
    CHECK(it1 >= it2);
    CHECK_FALSE(it1 != it2);
    CHECK_FALSE(it1 < it2);
    CHECK_FALSE(it1 > it2);
}
