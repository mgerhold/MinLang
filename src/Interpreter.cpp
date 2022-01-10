//
// Created by coder2k on 06.01.2022.
//

#include <iostream>
#include "Interpreter.hpp"
#include "Statement.hpp"

void Interpreter::visit(const U64LiteralExpr& expression) {
    assert(expression.token.u64LiteralValue());
    mResult = expression.token.u64LiteralValue().value();
}

void Interpreter::visit(const StringLiteralExpr& expression) {
    assert(expression.token.stringLiteralValue());
    mResult = std::string{ expression.token.stringLiteralValue().value() };
}

void Interpreter::visit(const GroupingExpr& expression) {
    evaluate(expression.subExpression);
}

void Interpreter::visit(const BinaryExpr& expression) {
    evaluate(expression.lhs);
    const auto lhsEvaluated = std::move(mResult);
    evaluate(expression.rhs);
    const auto rhsEvaluated = std::move(mResult);
    switch (expression.operator_.type) {
        case TokenType::Plus:
            if (not holds_alternative<u64>(lhsEvaluated) or lhsEvaluated.index() != rhsEvaluated.index()) {
                // TODO: throw runtime error
                assert(false);
            }
            mResult = get<u64>(lhsEvaluated) + get<u64>(rhsEvaluated);
            break;
        case TokenType::Asterisk:
            if (not holds_alternative<u64>(lhsEvaluated) or lhsEvaluated.index() != rhsEvaluated.index()) {
                // TODO: throw runtime error
                assert(false);
            }
            mResult = get<u64>(lhsEvaluated) * get<u64>(rhsEvaluated);
            break;
        default:
            // TODO: throw runtime error
            assert(false);
            break;
    }
}

void Interpreter::visit(ExpressionStatement& statement) {
    evaluate(statement.expression);
}

void Interpreter::visit(PrintStatement& statement) {
    evaluate(statement.expression);
    if (holds_alternative<u64>(mResult)) {
        mOutputStream << get<u64>(mResult) << "\n";
    } else if (holds_alternative<std::string>(mResult)) {
        mOutputStream << get<std::string>(mResult) << "\n";
    } else {
        // unsupported type
        assert(false);
    }
}

void Interpreter::visit(const UnaryExpr& expression) {
    using enum TokenType;
    evaluate(expression.operand);
    switch (expression.token.type) {
        case At:
            if (holds_alternative<u64>(mResult)) {
                mResult = std::to_string(get<u64>(mResult));
            }
            assert(holds_alternative<std::string>(mResult));
            break;
        case Plus:
            assert(holds_alternative<u64>(mResult));
            break;
        default:
            assert(false);
            break;
    }
}

void Interpreter::evaluate(const ExprNode& expression) {
    expression->accept(*this);
}

void Interpreter::execute(const StmtNode& statement) {
    statement->accept(*this);
}
