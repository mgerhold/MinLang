//
// Created by coder2k on 05.01.2022.
//

#pragma once

#include "MinLang.hpp"
#include "Token.hpp"
#include <format>
#include <string>
#include <memory>
#include <variant>

using Value = std::variant<u64, std::string>;

struct ExpressionVisitor;

struct Expression {
    explicit Expression(Token token) : token{ token } { }
    [[nodiscard]] virtual std::string toString() const = 0;
    virtual ~Expression() noexcept = default;

    virtual Value accept(const ExpressionVisitor& visitor) = 0;

    Token token;
};

using ExprNode = std::unique_ptr<Expression>;

struct U64LiteralExpr : public Expression {
    using Expression::Expression;

    [[nodiscard]] std::string toString() const override {
        return std::to_string(token.u64LiteralValue().value()) + "u";
    }

    [[nodiscard]] Value accept(const ExpressionVisitor& visitor) override;
};

struct StringLiteralExpr : public Expression {
    using Expression::Expression;

    [[nodiscard]] std::string toString() const override {
        return std::string{ token.lexeme };
    }

    [[nodiscard]] Value accept(const ExpressionVisitor& visitor) override;
};

struct GroupingExpr : public Expression {
    GroupingExpr(Token token, ExprNode subExpression)
        : Expression{ token },
          subExpression{ std::move(subExpression) } { }

    [[nodiscard]] std::string toString() const override {
        return std::format("({})", subExpression->toString());
    }

    [[nodiscard]] Value accept(const ExpressionVisitor& visitor) override;

    ExprNode subExpression;
};