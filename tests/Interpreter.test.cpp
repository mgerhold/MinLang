//
// Created by coder2k on 06.01.2022.
//

#include "Expression.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "TypeChecker.hpp"
#include "Interpreter.hpp"
#include <gtest/gtest.h>
#include <sstream>

using namespace std::string_view_literals;

TEST(InterpreterTests, EvaluateU64LiteralExpression) {
    const auto source = "42u;\"test\";"sv;
    auto lexer = Lexer{ source };
    const auto tokens = lexer.getTokens();
    auto parser = Parser{ tokens };
    const auto statements = parser.parse();
    ASSERT_EQ(statements.size(), 2);

    auto typeChecker = TypeChecker{};
    for (const auto& statement : statements) {
        typeChecker.check(statement);
    }
    ASSERT_TRUE(typeChecker.ok());

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

    auto typeChecker = TypeChecker{};
    for (const auto& statement : statements) {
        typeChecker.check(statement);
    }
    ASSERT_TRUE(typeChecker.ok());

    ASSERT_TRUE(dynamic_cast<ExpressionStatement*>(statements.at(0).get()));
    auto statement = dynamic_cast<ExpressionStatement*>(statements.at(0).get());
    auto interpreter = Interpreter{};
    interpreter.evaluate(statement->expression);
    auto value = interpreter.getResult();
    ASSERT_TRUE(holds_alternative<u64>(value));
    EXPECT_EQ(get<u64>(value), 42);
}

TEST(InterpreterTests, EvaluateMultipleBinaryExpressions) {
    const auto source = "40u + 2u + 8u + 10u;"sv;
    auto lexer = Lexer{ source };
    const auto tokens = lexer.getTokens();
    auto parser = Parser{ tokens };
    const auto statements = parser.parse();
    ASSERT_EQ(statements.size(), 1);

    auto typeChecker = TypeChecker{};
    for (const auto& statement : statements) {
        typeChecker.check(statement);
    }
    ASSERT_TRUE(typeChecker.ok());

    ASSERT_TRUE(dynamic_cast<ExpressionStatement*>(statements.at(0).get()));
    auto statement = dynamic_cast<ExpressionStatement*>(statements.at(0).get());
    auto interpreter = Interpreter{};
    interpreter.evaluate(statement->expression);
    auto value = interpreter.getResult();
    ASSERT_TRUE(holds_alternative<u64>(value));
    EXPECT_EQ(get<u64>(value), 60);
}

TEST(InterpreterTests, EvaluateGroupedBinaryExpressions) {
    const auto source = "40u + (2u + 8u + 10u);"sv;
    auto lexer = Lexer{ source };
    const auto tokens = lexer.getTokens();
    auto parser = Parser{ tokens };
    const auto statements = parser.parse();
    ASSERT_EQ(statements.size(), 1);

    auto typeChecker = TypeChecker{};
    for (const auto& statement : statements) {
        typeChecker.check(statement);
    }
    ASSERT_TRUE(typeChecker.ok());

    ASSERT_TRUE(dynamic_cast<ExpressionStatement*>(statements.at(0).get()));
    auto statement = dynamic_cast<ExpressionStatement*>(statements.at(0).get());
    auto interpreter = Interpreter{};
    interpreter.evaluate(statement->expression);
    auto value = interpreter.getResult();
    ASSERT_TRUE(holds_alternative<u64>(value));
    EXPECT_EQ(get<u64>(value), 60);
}

TEST(InterpreterTests, EvaluateUsingOperatorPrecedence) {
    const auto source = "2u + 3u * 4u;"sv;
    auto lexer = Lexer{ source };
    const auto tokens = lexer.getTokens();
    auto parser = Parser{ tokens };
    const auto statements = parser.parse();
    ASSERT_EQ(statements.size(), 1);

    auto typeChecker = TypeChecker{};
    for (const auto& statement : statements) {
        typeChecker.check(statement);
    }
    ASSERT_TRUE(typeChecker.ok());

    ASSERT_TRUE(dynamic_cast<ExpressionStatement*>(statements.at(0).get()));
    auto statement = dynamic_cast<ExpressionStatement*>(statements.at(0).get());
    auto interpreter = Interpreter{};
    interpreter.evaluate(statement->expression);
    auto value = interpreter.getResult();
    ASSERT_TRUE(holds_alternative<u64>(value));
    EXPECT_EQ(get<u64>(value), 14);
}

TEST(InterpreterTests, EvaluateGroupedExpressionsUsingOperatorPrecedence) {
    const auto source = "2u * (3u + 4u) + 6u * (3u + 2u * (7u + 2u));"sv;
    auto lexer = Lexer{ source };
    const auto tokens = lexer.getTokens();
    auto parser = Parser{ tokens };
    const auto statements = parser.parse();
    ASSERT_EQ(statements.size(), 1);

    auto typeChecker = TypeChecker{};
    for (const auto& statement : statements) {
        typeChecker.check(statement);
    }
    ASSERT_TRUE(typeChecker.ok());

    ASSERT_TRUE(dynamic_cast<ExpressionStatement*>(statements.at(0).get()));
    auto statement = dynamic_cast<ExpressionStatement*>(statements.at(0).get());
    auto interpreter = Interpreter{};
    interpreter.evaluate(statement->expression);
    auto value = interpreter.getResult();
    ASSERT_TRUE(holds_alternative<u64>(value));
    EXPECT_EQ(get<u64>(value), 140);
}

TEST(InterpreterTests, ExecutePrintStatement) {
    const auto source = "print \"Test\";"sv;
    auto lexer = Lexer{ source };
    const auto tokens = lexer.getTokens();
    auto parser = Parser{ tokens };
    const auto statements = parser.parse();
    ASSERT_EQ(statements.size(), 1);

    auto typeChecker = TypeChecker{};
    for (const auto& statement : statements) {
        typeChecker.check(statement);
    }
    ASSERT_TRUE(typeChecker.ok());

    ASSERT_TRUE(dynamic_cast<PrintStatement*>(statements.at(0).get()));
    std::stringstream sstream;
    auto interpreter = Interpreter{ sstream };
    interpreter.execute(statements.at(0));
    EXPECT_EQ(sstream.str(), "Test\n");
}

TEST(InterpreterTests, ExecuteMultiplePrintStatements) {
    const auto source = "print \"Test\"; print @42u; print @(2u * 3u);"sv;
    auto lexer = Lexer{ source };
    const auto tokens = lexer.getTokens();
    auto parser = Parser{ tokens };
    const auto statements = parser.parse();
    ASSERT_EQ(statements.size(), 3);

    auto typeChecker = TypeChecker{};
    for (const auto& statement : statements) {
        typeChecker.check(statement);
    }
    ASSERT_TRUE(typeChecker.ok());

    for (const auto& statement : statements) {
        ASSERT_TRUE(dynamic_cast<PrintStatement*>(statement.get()));
    }
    std::stringstream sstream;
    auto interpreter = Interpreter{ sstream };
    for (const auto& statement : statements) {
        interpreter.execute(statement);
    }
    EXPECT_EQ(sstream.str(), "Test\n42\n6\n");
}