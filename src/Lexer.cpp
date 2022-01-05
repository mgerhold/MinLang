//
// Created by coder2k on 04.01.2022.
//

#include <array>
#include <iostream>
#include <unordered_map>
#include <utility>
#include "Lexer.hpp"

using namespace std::string_view_literals;

std::vector<Token> Lexer::getTokens() {
    try {
        while (not isAtEnd()) {
            const auto singleCharToken = tokenTypeFor(peek());
            if (singleCharToken != TokenType::None) {
                addToken(singleCharToken, mSource.substr(mCurrent, 1));
                consume();
                continue;
            }
            if (peek() == '"') {
                stringLiteral();
                continue;
            }
            if (std::isspace(peek())) {
                consume();
                continue;
            }
            if (std::isdigit(peek())) {
                numberLiteral();
                continue;
            }
            keywordOrIdentifier();
        }
    } catch (const LexerError& error) {
        std::cout << "Lexer error: " << error.what() << "\n";
    }
    addToken(TokenType::EndOfFile, ""sv);
    return std::move(mTokens);
}

void Lexer::stringLiteral() {
    const auto startPosition = mCurrent;
    consume('"', "Expected '\"' at the start of a string literal.");
    while (not isAtEnd() and peek() != '"') {
        consume();
    }
    if (isAtEnd()) {
        throw error("Expected string termination, got end of file.");
    }
    consume('"', "Expected '\"' at the end of a string literal.");
    addToken(TokenType::StringLiteral, mSource.substr(startPosition, mCurrent - startPosition));
}

void Lexer::numberLiteral() {
    const auto startPosition = mCurrent;
    consume();
    while (not isAtEnd() and std::isdigit(peek())) {
        consume();
    }
    if (isAtEnd()) {
        throw error("Expected literal specifier at the end of a number literal, got end of file.");
    }
    consume('u', "Expected number literal specifier.");
    addToken(TokenType::U64Literal, mSource.substr(startPosition, mCurrent - startPosition));
}

void Lexer::keywordOrIdentifier() {
    if (not std::isalpha(peek())) {
        throw error("Identifiers must start with a letter.");
    }
    const auto startPosition = mCurrent;
    while (not isAtEnd() and std::isalnum(peek())) {
        consume();
    }
    const auto lexeme = mSource.substr(startPosition, mCurrent - startPosition);

    const auto token = tokenTypeFor(lexeme);
    assert(token != TokenType::None);
    addToken(token, lexeme);
}

constexpr bool Lexer::isAtEnd() const {
    return (mCurrent >= mSource.length());
}

constexpr char Lexer::peek() const {
    return mSource.at(mCurrent);
}

constexpr bool Lexer::check(char toCheck) const {
    return peek() == toCheck;
}

constexpr std::string_view Lexer::consume() {
    if (peek() == '\n') {
        ++mLine;
        mColumn = 0;
    } else {
        ++mColumn;
    }
    return mSource.substr(mCurrent++, 1);
}

constexpr std::string_view Lexer::consume(char toConsume, const std::string& errorMessage) {
    if (!check(toConsume)) {
        throw LexerError(mLine, mColumn, errorMessage);
    }
    return consume();
}

constexpr bool Lexer::match(char toMatch) {
    if (!check(toMatch)) {
        return false;
    }
    consume();
    return true;
}

LexerError Lexer::error(const std::string& message) const {
    return LexerError{ mLine, mColumn, message };
}

void Lexer::addToken(TokenType type, std::string_view lexeme) {
    mTokens.emplace_back(lexeme, mLine, mColumn, type);
}

constexpr TokenType Lexer::tokenTypeFor(char c) {
    constexpr auto singleCharTokens =
            std::to_array<std::pair<char, TokenType>>({
                    { '(', TokenType::LeftParenthesis },
                    { ')', TokenType::RightParenthesis },
                    { '=', TokenType::Equals },
                    { ';', TokenType::Semicolon },
                    { '+', TokenType::Plus },
                    { '@', TokenType::At },
            });
    for (const auto [singleChar, tokenType] : singleCharTokens) {
        if (singleChar == c) {
            return tokenType;
        }
    }
    return TokenType::None;
}

constexpr TokenType Lexer::tokenTypeFor(std::string_view lexeme) {
    constexpr auto keywordTokens =
            std::to_array<std::pair<std::string_view, TokenType>>({
                    { "const"sv, TokenType::Const },
                    { "mutable"sv, TokenType::Mutable },
                    { "print"sv, TokenType::Print },
    });
    for (const auto [keyword, tokenType] : keywordTokens) {
        if (keyword == lexeme) {
            return tokenType;
        }
    }
    return TokenType::Identifier;
}
