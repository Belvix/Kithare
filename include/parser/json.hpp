/*
 * This file is a part of the Kithare programming language source code.
 * The source code for Kithare programming language is distributed under the MIT license.
 * Copyright (C) 2021 Kithare Organization
 *
 * include/parser/json.hpp
 * Provides functions to represent parser types' instances as JSON string.
 */

#pragma once

#include <vector>

#include "utility/string.hpp"
#include "parser/token.hpp"


namespace kh {
    std::u32string json(const std::vector<kh::Token>& tokens);
}
