//
// Created by coder2k on 10.01.2022.
//

#pragma once

#include "StatementVisitor.hpp"
#include "ExpressionVisitor.hpp"
#include "DataTypes.hpp"
#include "TypeError.hpp"

class TypeChecker : public StatementVisitor, public ExpressionVisitor {
public:
    void visit(const U64LiteralExpr& expression) override;
    void visit(const StringLiteralExpr& expression) override;
    void visit(const GroupingExpr& expression) override;
    void visit(const BinaryExpr& expression) override;
    void visit(ExpressionStatement& statement) override;
    void visit(PrintStatement& statement) override;

    void check(const ExprNode& expression);
    void check(const StmtNode& statement);

    [[nodiscard]] bool ok() const;
    [[nodiscard]] static TypeError error(const std::string& message, Token token);
    void visit(const UnaryExpr& expression) override;

private:
    DataType mResult{ DataType::None };
    bool mHadError{ false };
};
