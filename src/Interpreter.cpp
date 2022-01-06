//
// Created by coder2k on 06.01.2022.
//

#include "Interpreter.hpp"

void Interpreter::visit(const U64LiteralExpr& expression) {
    assert(expression.token.u64LiteralValue());
    result = expression.token.u64LiteralValue().value();
}

void Interpreter::visit(const StringLiteralExpr& expression) {
    assert(expression.token.stringLiteralValue());
    result = std::string{ expression.token.stringLiteralValue().value() };
}

void Interpreter::visit(const GroupingExpr& expression) {
    evaluate(expression.subExpression);
}

void Interpreter::visit(const BinaryExpr& expression) {
    evaluate(expression.lhs);
    const auto lhsEvaluated = result;
    evaluate(expression.rhs);
    const auto rhsEvaluated = result;
    switch (expression.operator_.type) {
        case TokenType::Plus:
            if (not holds_alternative<u64>(lhsEvaluated) or lhsEvaluated.index() != rhsEvaluated.index()) {
                // TODO: throw runtime error
                assert(false);
            }
            result = get<u64>(lhsEvaluated) + get<u64>(rhsEvaluated);
            break;
        default:
            // TODO: throw runtime error
            assert(false);
            break;
    }
}

void Interpreter::evaluate(const ExprNode& expression) {
    expression->accept(*this);
}
