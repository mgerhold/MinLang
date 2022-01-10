//
// Created by coder2k on 06.01.2022.
//

#include "Expression.hpp"
#include "ExpressionVisitor.hpp"

void U64LiteralExpr::accept(ExpressionVisitor& visitor) {
    visitor.visit(*this);
}

void StringLiteralExpr::accept(ExpressionVisitor& visitor) {
    visitor.visit(*this);
}

void GroupingExpr::accept(ExpressionVisitor& visitor) {
    visitor.visit(*this);
}

void BinaryExpr::accept(ExpressionVisitor& visitor) {
    visitor.visit(*this);
}

void UnaryExpr::accept(ExpressionVisitor& visitor) {
    visitor.visit(*this);
}
