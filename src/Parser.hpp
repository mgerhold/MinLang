//
// Created by coder2k on 05.01.2022.
//

#pragma once

#include "Token.hpp"
#include "Expression.hpp"
#include "Statement.hpp"
#include <vector>

/* statement            -> expression ";"
 *                       | "print" expression ";" ;
 * expression           -> term ;
 * term                 -> factor ("+" factor)* ;
 * factor               -> unary ("*" unary)* ;
 * unary                -> primary | ("@" | "-") unary;
 * primary              -> STRING_LITERAL
 *                       | U64_LITERAL
 *                       | grouping ;
 * grouping             -> "(" expression ")" ;
 */

using StatementList = std::vector<StmtNode>;

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    [[nodiscard]] StatementList parse();
    [[nodiscard]] constexpr bool ok() const {
        return not hadError;
    }

private:
    [[nodiscard]] StmtNode statement();
    [[nodiscard]] StmtNode exprStatement();
    [[nodiscard]] StmtNode printStatement();
    [[nodiscard]] ExprNode expression();
    [[nodiscard]] ExprNode term();
    [[nodiscard]] ExprNode factor();
    [[nodiscard]] ExprNode unary();
    [[nodiscard]] ExprNode primary();
    [[nodiscard]] ExprNode grouping();
    [[nodiscard]] bool isAtEnd() const;
    [[nodiscard]] const Token& peek() const;
    Token consume();
    Token consume(TokenType expect, std::string_view errorMessage);
    [[nodiscard]] bool check(TokenType type) const;
    [[nodiscard]] bool match(TokenType type);
    [[nodiscard]] Token previous() const;

private:
    const std::vector<Token>& mTokens;
    uz mCurrent{ 0 };
    bool hadError{ false };
};
