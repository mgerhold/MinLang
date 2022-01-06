//
// Created by coder2k on 06.01.2022.
//

#pragma once

#include "MinLang.hpp"
#include "ExpressionVisitor.hpp"
#include "Expression.hpp"
#include <variant>

class Interpreter : public ExpressionVisitor {
public:
    [[nodiscard]] Value visit(const U64LiteralExpr& expression) const override;
    [[nodiscard]] Value visit(const StringLiteralExpr& expression) const override;
    [[nodiscard]] Value visit(const GroupingExpr& expression) const override;

    [[nodiscard]] Value evaluate(const ExprNode& expression) const;
};
