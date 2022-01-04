//
// Created by coder2k on 04.01.2022.
//

#pragma once

#include "MinLang.hpp"
#include <charconv>

struct Token {
    Token(std::string_view lexeme, uz line, uz column) : lexeme{ lexeme }, line{ line }, column{ column } {}
    virtual ~Token() = default;

    std::string_view lexeme;
    uz line;
    uz column;
};

struct Const : public Token {
    using Token::Token;
};

struct Identifier : public Token {
    using Token::Token;
};

struct Equals : public Token {
    using Token::Token;
};

struct StringLiteral : public Token {
    using Token::Token;

    [[nodiscard]] constexpr std::string_view value() const {
        return lexeme.substr(1, lexeme.size() - 2);
    }
};

struct Semicolon : public Token {
    using Token::Token;
};

struct Mutable : public Token {
    using Token::Token;
};

struct U64Literal : public Token {
    using Token::Token;

    [[nodiscard]] u64 value() const {
        u64 result;
        const auto fromCharsResult = std::from_chars(lexeme.data(), lexeme.data() + lexeme.size() - 1, result);
        assert(fromCharsResult.ec != std::errc::invalid_argument);
        return result;
    }
};

struct Plus : public Token {
    using Token::Token;
};

struct Print : public Token {
    using Token::Token;
};

struct At : public Token {
    using Token::Token;
};

struct EndOfFile : public Token {
    using Token::Token;
};