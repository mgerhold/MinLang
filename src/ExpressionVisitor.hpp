//
// Created by coder2k on 06.01.2022.
//

#pragma once

#include "Expression.hpp"

struct ExpressionVisitor {
    virtual Value visit(const U64LiteralExpr& expression) const = 0;
    virtual Value visit(const StringLiteralExpr& expression) const = 0;
    virtual Value visit(const GroupingExpr& expression) const = 0;
};