//
// Created by coder2k on 10.01.2022.
//

#pragma once

#include "Statement.hpp"

struct StatementVisitor {
    virtual void visit(ExpressionStatement& statement) = 0;
    virtual void visit(PrintStatement& statement) = 0;
};