//
// Created by coder2k on 05.01.2022.
//

#pragma once

#include "Token.hpp"
#include "Expression.hpp"
#include <vector>

/*
 * expression           -> primary ;
 * primary              -> STRING_LITERAL
 *                       | U64_LITERAL
 *                       | grouping ;
 * grouping             -> "(" expression ")" ;
 */

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    [[nodiscard]] ASTNode parse();

private:
    [[nodiscard]] ASTNode expression();
    [[nodiscard]] ASTNode primary();
    [[nodiscard]] ASTNode grouping();
    [[nodiscard]] bool isAtEnd() const;
    [[nodiscard]] const Token& peek() const;
    Token consume();
    Token consume(TokenType expect, std::string_view errorMessage);
    [[nodiscard]] bool check(TokenType type) const;
    [[nodiscard]] bool match(TokenType type);

private:
    const std::vector<Token>& mTokens;
    uz mCurrent{ 0 };
};
