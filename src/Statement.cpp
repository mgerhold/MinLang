//
// Created by coder2k on 10.01.2022.
//

#include "Statement.hpp"
#include "StatementVisitor.hpp"

void ExpressionStatement::accept(StatementVisitor& visitor) {
    visitor.visit(*this);
}

void PrintStatement::accept(StatementVisitor& visitor)  {
    visitor.visit(*this);
}
