//
// Created by coder2k on 06.01.2022.
//

#pragma once

#include "MinLang.hpp"
#include "ExpressionVisitor.hpp"
#include "Expression.hpp"
#include <variant>

using Value = std::variant<u64, std::string>;

class Interpreter : public ExpressionVisitor {
public:
    void visit(const U64LiteralExpr& expression) override;
    void visit(const StringLiteralExpr& expression) override;
    void visit(const GroupingExpr& expression) override;
    void visit(const BinaryExpr& expression) override;

    [[nodiscard]] Value getResult() const {
        return result;
    }
    void evaluate(const ExprNode& expression);

private:
    Value result{};
};
