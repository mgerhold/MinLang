//
// Created by coder2k on 05.01.2022.
//

#pragma once

#include "MinLang.hpp"
#include "Token.hpp"
#include <format>
#include <stdexcept>

class ParserError : public std::exception {
public:
    ParserError(Token token, std::string_view message)
        : mWhat{ std::format("{} at '{}' (line {}, column {})", message, token.lexeme, token.line, token.column) } { }

    [[nodiscard]] const char* what() const noexcept override {
        return mWhat.c_str();
    }

private:
    std::string mWhat;
};