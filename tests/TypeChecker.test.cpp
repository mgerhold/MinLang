//
// Created by coder2k on 10.01.2022.
//

#include "Lexer.hpp"
#include "Parser.hpp"
#include "TypeChecker.hpp"
#include <gtest/gtest.h>
#include <string_view>

using namespace std::string_view_literals;

TEST(TypeCheckerTests, FailOnMismatchedTypes) {
    const auto source = "42u + \"answer\";"sv;
    auto lexer = Lexer{ source };
    const auto tokens = lexer.getTokens();
    auto parser = Parser{ tokens };
    const auto statements = parser.parse();
    ASSERT_EQ(statements.size(), 1);
    ASSERT_TRUE(dynamic_cast<ExpressionStatement*>(statements.at(0).get()));

    auto typeChecker = TypeChecker{};
    typeChecker.check(statements.at(0));
    EXPECT_FALSE(typeChecker.ok());
}

TEST(TypeCheckerTests, FailOnPrintingNumber) {
    const auto source = "print 42u;"sv;
    auto lexer = Lexer{ source };
    const auto tokens = lexer.getTokens();
    auto parser = Parser{ tokens };
    const auto statements = parser.parse();
    ASSERT_EQ(statements.size(), 1);
    ASSERT_TRUE(dynamic_cast<PrintStatement*>(statements.at(0).get()));

    auto typeChecker = TypeChecker{};
    typeChecker.check(statements.at(0));
    EXPECT_FALSE(typeChecker.ok());
}

TEST(TypeCheckerTests, ConversionToString) {
    const auto source = "print @42u;"sv;
    auto lexer = Lexer{ source };
    const auto tokens = lexer.getTokens();
    auto parser = Parser{ tokens };
    const auto statements = parser.parse();
    ASSERT_EQ(statements.size(), 1);
    ASSERT_TRUE(dynamic_cast<PrintStatement*>(statements.at(0).get()));

    auto typeChecker = TypeChecker{};
    typeChecker.check(statements.at(0));
    EXPECT_TRUE(typeChecker.ok());
}