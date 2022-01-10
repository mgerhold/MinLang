//
// Created by coder2k on 06.01.2022.
//

#pragma once

#include "Expression.hpp"

struct ExpressionVisitor {
    virtual void visit(const U64LiteralExpr& expression) = 0;
    virtual void visit(const StringLiteralExpr& expression) = 0;
    virtual void visit(const GroupingExpr& expression) = 0;
    virtual void visit(const BinaryExpr& expression) = 0;
    virtual void visit(const UnaryExpr& expression) = 0;
};