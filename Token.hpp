//
// Created by coder2k on 04.01.2022.
//

#pragma once

#include "MinLang.hpp"
#include <charconv>

struct Token {
    std::string_view lexeme;
    uz line;
    uz column;
};

struct Const : public Token {};

struct Identifier : public Token {};

struct Equals : public Token {};

struct StringLiteral : public Token {
    [[nodiscard]] constexpr std::string_view value() const {
        return lexeme.substr(1, lexeme.size() - 2);
    }
};

struct Semicolon : public Token {};

struct Mutable : public Token {};

struct U64Literal : public Token {
    [[nodiscard]] u64 value() const {
        u64 result;
        const auto fromCharsResult = std::from_chars(lexeme.data(), lexeme.data() + lexeme.size() - 1, result);
        assert(fromCharsResult.ec != std::errc::invalid_argument);
        return result;
    }
};

struct Plus : public Token {};

struct Print : public Token {};

struct At : public Token {};