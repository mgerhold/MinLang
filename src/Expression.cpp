//
// Created by coder2k on 06.01.2022.
//

#include "Expression.hpp"
#include "ExpressionVisitor.hpp"

[[nodiscard]] Value U64LiteralExpr::accept(const ExpressionVisitor& visitor) {
    return visitor.visit(*this);
}

[[nodiscard]] Value StringLiteralExpr::accept(const ExpressionVisitor& visitor) {
    return visitor.visit(*this);
}

[[nodiscard]] Value GroupingExpr::accept(const ExpressionVisitor& visitor) {
    return visitor.visit(*this);
}
