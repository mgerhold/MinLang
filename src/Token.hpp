//
// Created by coder2k on 04.01.2022.
//

#pragma once

#include "MinLang.hpp"
#include <charconv>
#include <optional>

enum class TokenType {
    None,
    Const,
    Identifier,
    Equals,
    StringLiteral,
    Semicolon,
    Mutable,
    U64Literal,
    Plus,
    Print,
    At,
    LeftParenthesis,
    RightParenthesis,
    EndOfFile,
};

struct Token final {
    Token(std::string_view lexeme, uz line, uz column, TokenType type)
        : lexeme{ lexeme },
          line{ line },
          column{ column },
          type{ type } { }

    std::string_view lexeme;
    uz line;
    uz column;
    TokenType type;

    [[nodiscard]] std::optional<std::string_view> stringLiteralValue() const {
        if (type != TokenType::StringLiteral) {
            return {};
        }
        return lexeme.substr(1, lexeme.size() - 2);
    }

    [[nodiscard]] std::optional<u64> u64LiteralValue() const {
        if (type != TokenType::U64Literal) {
            return {};
        }
        u64 result;
        const auto fromCharsResult = std::from_chars(lexeme.data(), lexeme.data() + lexeme.size() - 1, result);
        assert(fromCharsResult.ec != std::errc::invalid_argument);
        return result;
    }
};