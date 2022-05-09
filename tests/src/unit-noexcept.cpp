//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++ (supporting code)
// |  |  |__   |  |  | | | |  version 3.11.1
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2022 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT

#include "doctest_compatibility.h"

// disable -Wnoexcept due to struct pod_bis
DOCTEST_GCC_SUPPRESS_WARNING_PUSH
DOCTEST_GCC_SUPPRESS_WARNING("-Wnoexcept")

#include <nlohmann/json.hpp>

using nlohmann::json;

namespace
{
enum test
{
};

struct pod {};
struct pod_bis {};

void to_json(json& /*unused*/, pod /*unused*/) noexcept;
void to_json(json& /*unused*/, pod_bis /*unused*/);
void from_json(const json& /*unused*/, pod /*unused*/) noexcept;
void from_json(const json& /*unused*/, pod_bis /*unused*/);
void to_json(json& /*unused*/, pod /*unused*/) noexcept {}
void to_json(json& /*unused*/, pod_bis /*unused*/) {}
void from_json(const json& /*unused*/, pod /*unused*/) noexcept {}
void from_json(const json& /*unused*/, pod_bis /*unused*/) {}

json* j = nullptr;

static_assert(noexcept(json{}), "");
static_assert(noexcept(nlohmann::to_json(*j, 2)), "");
static_assert(noexcept(nlohmann::to_json(*j, 2.5)), "");
static_assert(noexcept(nlohmann::to_json(*j, true)), "");
static_assert(noexcept(nlohmann::to_json(*j, test{})), "");
static_assert(noexcept(nlohmann::to_json(*j, pod{})), "");
static_assert(!noexcept(nlohmann::to_json(*j, pod_bis{})), "");
static_assert(noexcept(json(2)), "");
static_assert(noexcept(json(test{})), "");
static_assert(noexcept(json(pod{})), "");
static_assert(noexcept(j->get<pod>()), "");
static_assert(!noexcept(j->get<pod_bis>()), "");
static_assert(noexcept(json(pod{})), "");
} // namespace

TEST_CASE("runtime checks")
{
    SECTION("nothrow-copy-constructible exceptions")
    {
        // for ERR60-CPP (https://github.com/nlohmann/json/issues/531):
        // Exceptions should be nothrow-copy-constructible. However, compilers
        // treat std::runtime_exception differently in this regard. Therefore,
        // we can only demand nothrow-copy-constructibility for our exceptions
        // if std::runtime_exception is.
        CHECK(std::is_nothrow_copy_constructible<json::exception>::value == std::is_nothrow_copy_constructible<std::runtime_error>::value);
        CHECK(std::is_nothrow_copy_constructible<json::parse_error>::value == std::is_nothrow_copy_constructible<std::runtime_error>::value);
        CHECK(std::is_nothrow_copy_constructible<json::invalid_iterator>::value == std::is_nothrow_copy_constructible<std::runtime_error>::value);
        CHECK(std::is_nothrow_copy_constructible<json::type_error>::value == std::is_nothrow_copy_constructible<std::runtime_error>::value);
        CHECK(std::is_nothrow_copy_constructible<json::out_of_range>::value == std::is_nothrow_copy_constructible<std::runtime_error>::value);
        CHECK(std::is_nothrow_copy_constructible<json::other_error>::value == std::is_nothrow_copy_constructible<std::runtime_error>::value);
    }

    SECTION("silence -Wunneeded-internal-declaration errors")
    {
        j = nullptr;
        json j2;
        to_json(j2, pod());
        to_json(j2, pod_bis());
        from_json(j2, pod());
        from_json(j2, pod_bis());
    }
}

DOCTEST_GCC_SUPPRESS_WARNING_POP

#include "print_meta.cpp" // NOLINT(bugprone-suspicious-include)
