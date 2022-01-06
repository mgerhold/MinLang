//
// Created by coder2k on 06.01.2022.
//

#include "Interpreter.hpp"

Value Interpreter::visit(const U64LiteralExpr& expression) const {
    assert(expression.token.u64LiteralValue());
    return expression.token.u64LiteralValue().value();
}

Value Interpreter::visit(const StringLiteralExpr& expression) const {
    assert(expression.token.stringLiteralValue());
    return std::string{ expression.token.stringLiteralValue().value() };
}

Value Interpreter::visit(const GroupingExpr& expression) const {
    return evaluate(expression.subExpression);
}

Value Interpreter::evaluate(const ExprNode& expression) const {
    return expression->accept(*this);
}
