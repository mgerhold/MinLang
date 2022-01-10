//
// Created by coder2k on 06.01.2022.
//

#pragma once

#include "Token.hpp"
#include "Expression.hpp"
#include <memory>

struct StatementVisitor;

struct Statement {
    explicit Statement(Token token) : token{ token } { }
    virtual ~Statement() noexcept = default;

    virtual void accept(StatementVisitor& visitor) = 0;

    Token token;
};

using StmtNode = std::unique_ptr<Statement>;

struct ExpressionStatement : public Statement {
    ExpressionStatement(Token token, ExprNode expression) : Statement{ token }, expression{ std::move(expression) } { }

    void accept(StatementVisitor& visitor) override;

    ExprNode expression;
};

struct PrintStatement : public Statement {
    PrintStatement(Token token, ExprNode expression) : Statement{ token }, expression{ std::move(expression) } { }

    void accept(StatementVisitor& visitor) override;

    ExprNode expression;
};