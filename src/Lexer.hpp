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
    [[nodiscard]] std::vector<std::unique_ptr<Token>> getTokens();

private:
    void stringLiteral();
    void numberLiteral();
    void keywordOrIdentifier();

    [[nodiscard]] constexpr bool isAtEnd() const;
    [[nodiscard]] constexpr char peek() const; // returns the next char to look at
    [[nodiscard]] constexpr bool check(char toCheck) const; // checks if the next char is equal to toCheck
    constexpr void consume(); // advances the current position
    constexpr void consume(char toConsume, const std::string& errorMessage); // consumes the given character or throws if characters don't match
    [[nodiscard]] constexpr bool match(char toMatch); // tries to consume the given character, returns true on success
    LexerError error(const std::string& message) const;

    template<typename TokenType, typename... Args>
    void addToken(Args&&... args) {
        mTokens.emplace_back(std::make_unique<TokenType>(std::forward<Args>(args)..., mLine, mColumn));
    }

private:
    uz mCurrent{ 0 };
    uz mLine{ 0 };
    uz mColumn{ 0 };
    std::string_view mSource;
    std::vector<std::unique_ptr<Token>> mTokens;
};
