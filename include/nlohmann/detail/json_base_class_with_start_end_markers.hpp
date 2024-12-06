//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT

#pragma once

#include <string> // string::npos

#include <nlohmann/detail/abi_macros.hpp>

NLOHMANN_JSON_NAMESPACE_BEGIN
namespace detail
{

/*!
@brief Custom base struct of the @ref basic_json class.
This class exposes the start and end positions for all fields of a JSON object
with reference to the parsed input.
*/
struct json_base_class_with_start_end_markers
{
  public:
    size_t start_position = std::string::npos;
    size_t end_position = std::string::npos;
};

}  // namespace detail
NLOHMANN_JSON_NAMESPACE_END
