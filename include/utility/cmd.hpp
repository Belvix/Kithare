/*
 * This file is a part of the Kithare programming language source code.
 * The source code for Kithare programming language is distributed under the MIT license.
 * Copyright (C) 2021 Kithare Organization
 *
 * include/utility/cmd.hpp
 * Implements argument parsing for kithare commandline interface
 */

#pragma once

#include <vector>

#include "utility/string.hpp"


namespace kh {
    int run(const std::vector<std::u32string>& args);
}
