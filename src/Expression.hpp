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

struct ExpressionVisitor;

struct Expression {
    explicit Expression(Token token) : token{ token } { }
    virtual ~Expression() noexcept = default;

    virtual void accept(ExpressionVisitor& visitor) = 0;

    Token token;
};

using ExprNode = std::unique_ptr<Expression>;

struct U64LiteralExpr : public Expression {
    using Expression::Expression;

    void accept(ExpressionVisitor& visitor) override;
};

struct StringLiteralExpr : public Expression {
    using Expression::Expression;

    void accept(ExpressionVisitor& visitor) override;
};

struct GroupingExpr : public Expression {
    GroupingExpr(Token token, ExprNode subExpression)
        : Expression{ token },
          subExpression{ std::move(subExpression) } { }

    void accept(ExpressionVisitor& visitor) override;

    ExprNode subExpression;
};

struct BinaryExpr : public Expression {
    BinaryExpr(Token token, ExprNode lhs, Token operator_, ExprNode rhs)
        : Expression{ token },
          lhs{ std::move(lhs) },
          operator_{ operator_ },
          rhs{ std::move(rhs) } { }

    void accept(ExpressionVisitor& visitor) override;

    ExprNode lhs;
    Token operator_;
    ExprNode rhs;
};

struct UnaryExpr : public Expression {
    UnaryExpr(Token operator_, ExprNode operand)
        : Expression{ operator_ },
          operand{ std::move(operand) } { }

    void accept(ExpressionVisitor& visitor) override;

    ExprNode operand;
};