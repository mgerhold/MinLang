//
// Created by coder2k on 04.01.2022.
//

#pragma once

#include "MinLang.hpp"
#include "Token.hpp"
#include "LexerError.hpp"
#include <memory>
#include <vector>

class Lexer {
public:
    Lexer(std::string_view source) : mSource{ source } { }
    [[nodiscard]] std::vector<Token> getTokens();

private:
    void stringLiteral();
    void numberLiteral();
    void keywordOrIdentifier();

    [[nodiscard]] constexpr bool isAtEnd() const;
    [[nodiscard]] constexpr char peek() const; // returns the next char to look at
    [[nodiscard]] constexpr bool check(char toCheck) const; // checks if the next char is equal to toCheck
    constexpr std::string_view consume(); // advances the current position
    constexpr std::string_view consume(char toConsume, const std::string& errorMessage); // consumes the given character or throws if characters don't match
    [[nodiscard]] constexpr bool match(char toMatch); // tries to consume the given character, returns true on success
    LexerError error(const std::string& message) const;

    void addToken(TokenType type, std::string_view lexeme);
    [[nodiscard]] static constexpr TokenType tokenTypeFor(char c);
    [[nodiscard]] static constexpr TokenType tokenTypeFor(std::string_view lexeme);

private:
    uz mCurrent{ 0 };
    uz mLine{ 1 };
    uz mColumn{ 1 };
    std::string_view mSource;
    std::vector<Token> mTokens;
};
