//
// Created by coder2k on 10.01.2022.
//

#pragma once

#include <stdexcept>
#include <string>

struct TypeError : public std::logic_error {
public:
    using std::logic_error::logic_error;
};