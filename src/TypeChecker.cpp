//
// Created by coder2k on 10.01.2022.
//

#include "TypeChecker.hpp"
#include "TypeError.hpp"
#include "magic_enum/magic_enum.hpp"
#include <format>
#include <iostream>

void TypeChecker::visit(const U64LiteralExpr&) {
    mResult = DataType::Unsigned64;
}

void TypeChecker::visit(const StringLiteralExpr&) {
    mResult = DataType::String;
}

void TypeChecker::visit(const GroupingExpr& expression) {
    check(expression.subExpression);
}

void TypeChecker::visit(const BinaryExpr& expression) {
    check(expression.lhs);
    const auto leftType = mResult;
    check(expression.rhs);
    const auto rightType = mResult;
    if (leftType != rightType) {
        throw error(std::format("Type mismatch between '{}' and '{}'", magic_enum::enum_name(leftType),
                                magic_enum::enum_name(rightType)),
                    expression.operator_);
    }
}

void TypeChecker::visit(ExpressionStatement& statement) {
    check(statement.expression);
    mResult = DataType::None;
}

void TypeChecker::visit(PrintStatement& statement) {
    check(statement.expression);
    if (mResult != DataType::String) {
        throw error("Print statement expects string as parameter.", statement.token);
    }
    mResult = DataType::None;
}

void TypeChecker::visit(const UnaryExpr& expression) {
    check(expression.operand);
    using enum TokenType;
    switch (expression.token.type) {
        case At:
            mResult = DataType::String;
            return;
        case Plus:
            if (mResult != DataType::Unsigned64) {
                throw error("Unary '-' is only allowed for u64 values.", expression.token);
            }
            break;
        default:
            throw error(std::format("Unary operator '{}' is not supported for type '{}'.", expression.token.lexeme,
                                    magic_enum::enum_name(mResult)),
                        expression.token);
    }
}

void TypeChecker::check(const ExprNode& expression) {
    try {
        expression->accept(*this);
    } catch (const TypeError& e) {
        std::cerr << "Type error: " << e.what() << "\n";
        mHadError = true;
    }
}

void TypeChecker::check(const StmtNode& statement) {
    try {
        statement->accept(*this);
    } catch (const TypeError& e) {
        std::cerr << "Type error: " << e.what() << "\n";
        mHadError = true;
    }
}

bool TypeChecker::ok() const {
    return !mHadError;
}

TypeError TypeChecker::error(const std::string& message, Token token) {
    return TypeError{ std::format("{} (line {}, column {})", message, token.line, token.column) };
}
