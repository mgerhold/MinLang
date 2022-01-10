//
// Created by coder2k on 06.01.2022.
//

#pragma once

#include "MinLang.hpp"
#include "ExpressionVisitor.hpp"
#include "Expression.hpp"
#include "StatementVisitor.hpp"
#include <variant>
#include <iostream>

using Value = std::variant<u64, std::string>;

class Interpreter : public ExpressionVisitor, public StatementVisitor {
public:
    explicit Interpreter(std::ostream& outputStream = std::cout) : mOutputStream{ outputStream } { }

    void visit(const U64LiteralExpr& expression) override;
    void visit(const StringLiteralExpr& expression) override;
    void visit(const GroupingExpr& expression) override;
    void visit(const BinaryExpr& expression) override;

    [[nodiscard]] Value getResult() const {
        return mResult;
    }
    void evaluate(const ExprNode& expression);

    void visit(ExpressionStatement& statement) override;
    void visit(PrintStatement& statement) override;

    void execute(const StmtNode& statement);
    void visit(const UnaryExpr& expression) override;

private:
    Value mResult{};
    std::ostream& mOutputStream;
};
