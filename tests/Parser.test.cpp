//
// Created by coder2k on 06.01.2022.
//

#include "Lexer.hpp"
#include "Parser.hpp"
#include "ParserError.hpp"
#include <gtest/gtest.h>
#include <array>
#include <string_view>

using namespace std::string_view_literals;
using enum TokenType;

TEST(ParserTests, ParsePrintStatement) {
    const auto source = "print \"Hello\";print 42u;"sv;
    auto lexer = Lexer{ source };
    const auto tokens = lexer.getTokens();
    ASSERT_EQ(tokens.size(), 7);
    ASSERT_EQ(tokens.at(0).type, Print);
    ASSERT_EQ(tokens.at(1).type, StringLiteral);
    ASSERT_EQ(tokens.at(2).type, Semicolon);
    ASSERT_EQ(tokens.at(3).type, Print);
    ASSERT_EQ(tokens.at(4).type, U64Literal);
    ASSERT_EQ(tokens.at(5).type, Semicolon);
    ASSERT_EQ(tokens.at(6).type, EndOfFile);
    auto parser = Parser{ tokens };
    const auto statements = parser.parse();
    ASSERT_EQ(statements.size(), 2);
    ASSERT_TRUE(dynamic_cast<PrintStatement*>(statements.front().get()));
    // first print statement
    auto printStatement = dynamic_cast<PrintStatement*>(statements.front().get());
    EXPECT_EQ(printStatement->expression->token.type, StringLiteral);
    EXPECT_EQ(printStatement->expression->token.stringLiteralValue(), "Hello"sv);

    // second print statement
    ASSERT_TRUE(dynamic_cast<PrintStatement*>(statements.at(1).get()));
    printStatement = dynamic_cast<PrintStatement*>(statements.at(1).get());
    EXPECT_EQ(printStatement->expression->token.type, U64Literal);
    EXPECT_EQ(printStatement->expression->token.u64LiteralValue(), 42);
}

TEST(ParserTests, SyntaxErrorOnMissingSemicolon) {
    const auto source = R"(print "Hello")";
    auto lexer = Lexer{ source };
    const auto tokens = lexer.getTokens();
    ASSERT_EQ(tokens.size(), 3);
    ASSERT_EQ(tokens.at(0).type, Print);
    ASSERT_EQ(tokens.at(1).type, StringLiteral);
    ASSERT_EQ(tokens.at(2).type, EndOfFile);
    auto parser = Parser{ tokens };
    [[maybe_unused]] auto _ = parser.parse();
    EXPECT_FALSE(parser.ok());
}