//
// Created by coder2k on 06.01.2022.
//

#include "Expression.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"
#include <gtest/gtest.h>

using namespace std::string_view_literals;

TEST(InterpreterTests, EvaluateU64LiteralExpression) {
    const auto source = "42u;\"test\";"sv;
    auto lexer = Lexer{ source };
    const auto tokens = lexer.getTokens();
    auto parser = Parser{ tokens };
    const auto statements = parser.parse();
    ASSERT_EQ(statements.size(), 2);

    // first statement
    ASSERT_TRUE(dynamic_cast<ExpressionStatement*>(statements.at(0).get()));
    auto statement = dynamic_cast<ExpressionStatement*>(statements.at(0).get());
    auto interpreter = Interpreter{};
    interpreter.evaluate(statement->expression);
    auto value = interpreter.getResult();
    ASSERT_TRUE(holds_alternative<u64>(value));
    EXPECT_EQ(get<u64>(value), 42);

    // second statement
    ASSERT_TRUE(dynamic_cast<ExpressionStatement*>(statements.at(1).get()));
    statement = dynamic_cast<ExpressionStatement*>(statements.at(1).get());
    interpreter.evaluate(statement->expression);
    value = interpreter.getResult();
    ASSERT_TRUE(holds_alternative<std::string>(value));
    EXPECT_EQ(get<std::string>(value), "test");
}

TEST(InterpreterTests, EvaluateBinaryExpression) {
    const auto source = "40u + 2u;"sv;
    auto lexer = Lexer{ source };
    const auto tokens = lexer.getTokens();
    auto parser = Parser{ tokens };
    const auto statements = parser.parse();
    ASSERT_EQ(statements.size(), 1);

    ASSERT_TRUE(dynamic_cast<ExpressionStatement*>(statements.at(0).get()));
    auto statement = dynamic_cast<ExpressionStatement*>(statements.at(0).get());
    auto interpreter = Interpreter{};
    interpreter.evaluate(statement->expression);
    auto value = interpreter.getResult();
    ASSERT_TRUE(holds_alternative<u64>(value));
    EXPECT_EQ(get<u64>(value), 42);
}