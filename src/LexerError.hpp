//
// Created by coder2k on 04.01.2022.
//

#pragma once

#include "MinLang.hpp"
#include <format>
#include <stdexcept>

class LexerError : public std::exception {
public:
    LexerError(uz line, uz column, const std::string& message)
        : mWhat{ std::format("{} (line {}, column {})", message, line, column) } { }

    [[nodiscard]] const char* what() const noexcept override {
        return mWhat.c_str();
    }

private:
    std::string mWhat;
};