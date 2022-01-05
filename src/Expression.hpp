//
// Created by coder2k on 05.01.2022.
//

#pragma once

#include "MinLang.hpp"
#include "Token.hpp"
#include <format>
#include <string>
#include <memory>

struct Expression {
    explicit Expression(Token token) : token{ token } { }
    [[nodiscard]] virtual std::string toString() const = 0;
    virtual ~Expression() noexcept = default;

    Token token;
};

using ASTNode = std::unique_ptr<Expression>;

struct U64LiteralExpr : public Expression {
    using Expression::Expression;

    [[nodiscard]] std::string toString() const override {
        return std::to_string(token.u64LiteralValue().value()) + "u";
    }
};

struct StringLiteralExpr : public Expression {
    using Expression::Expression;

    [[nodiscard]] std::string toString() const override {
        return std::format("\"{}\"", token.lexeme);
    }
};

struct GroupingExpr : public Expression {
    GroupingExpr(Token token, ASTNode subExpression)
        : Expression{ token },
          subExpression{ std::move(subExpression) } { }

    [[nodiscard]] std::string toString() const override {
        return std::format("({})", subExpression->toString());
    }

    ASTNode subExpression;
};