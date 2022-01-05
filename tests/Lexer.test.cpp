//
// Created by coder2k on 04.01.2022.
//

#include "Lexer.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <vector>

using namespace std::string_view_literals;

TEST(Lexer, SingleToken) {
    using namespace std::string_view_literals;
    const auto source = "const"sv;
    auto lexer = Lexer{ source };
    const auto tokens = lexer.getTokens();
    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens.front().type, TokenType::Const);
    EXPECT_EQ(tokens.back().type, TokenType::EndOfFile);
}

class SingleTokensInLongSource : public ::testing::Test {
public:
    void SetUp() override {
        const auto source = R"(const thisIsAnIdentifier054Test="string literal";mutable 4297243u+print@())"sv;
        auto lexer = Lexer{ source };
        mTokens = lexer.getTokens();
        ASSERT_EQ(mTokens.size(), 13);
    }

protected:
    std::vector<Token> mTokens;
};

TEST_F(SingleTokensInLongSource, shouldScanConst) {
    EXPECT_EQ(mTokens.at(0).type, TokenType::Const);
    EXPECT_EQ(mTokens.at(0).lexeme, "const");
}

TEST_F(SingleTokensInLongSource, shouldScanIdentifier) {
    EXPECT_EQ(mTokens.at(1).type, TokenType::Identifier);
    EXPECT_EQ(mTokens.at(1).lexeme, "thisIsAnIdentifier054Test");
}

TEST_F(SingleTokensInLongSource, shouldScanEquals) {
    EXPECT_EQ(mTokens.at(2).type, TokenType::Equals);
    EXPECT_EQ(mTokens.at(2).lexeme, "=");
}

TEST_F(SingleTokensInLongSource, shouldScanStringLiteral) {
    EXPECT_EQ(mTokens.at(3).type, TokenType::StringLiteral);
    EXPECT_EQ(mTokens.at(3).lexeme, R"("string literal")");
    ASSERT_TRUE(mTokens.at(3).stringLiteralValue());
    EXPECT_EQ(mTokens.at(3).stringLiteralValue(), "string literal");
}

TEST_F(SingleTokensInLongSource, shouldScanSemicolon) {
    EXPECT_EQ(mTokens.at(4).type, TokenType::Semicolon);
    EXPECT_EQ(mTokens.at(4).lexeme, ";");
}

TEST_F(SingleTokensInLongSource, shouldScanMutable) {
    EXPECT_EQ(mTokens.at(5).type, TokenType::Mutable);
    EXPECT_EQ(mTokens.at(5).lexeme, "mutable");
}

TEST_F(SingleTokensInLongSource, shouldScanU64Literal) {
    EXPECT_EQ(mTokens.at(6).type, TokenType::U64Literal);
    EXPECT_EQ(mTokens.at(6).lexeme, "4297243u");
    EXPECT_EQ(mTokens.at(6).u64LiteralValue(), 4297243);
}

TEST_F(SingleTokensInLongSource, shouldScanPlus) {
    EXPECT_EQ(mTokens.at(7).type, TokenType::Plus);
    EXPECT_EQ(mTokens.at(7).lexeme, "+");
}

TEST_F(SingleTokensInLongSource, shouldScanPrint) {
    EXPECT_EQ(mTokens.at(8).type, TokenType::Print);
    EXPECT_EQ(mTokens.at(8).lexeme, "print");
}

TEST_F(SingleTokensInLongSource, shouldScanAt) {
    EXPECT_EQ(mTokens.at(9).type, TokenType::At);
    EXPECT_EQ(mTokens.at(9).lexeme, "@");
}

TEST_F(SingleTokensInLongSource, shouldScanLeftParenthesis) {
    EXPECT_EQ(mTokens.at(10).type, TokenType::LeftParenthesis);
    EXPECT_EQ(mTokens.at(10).lexeme, "(");
}

TEST_F(SingleTokensInLongSource, shouldScanRightParenthesis) {
    EXPECT_EQ(mTokens.at(11).type, TokenType::RightParenthesis);
    EXPECT_EQ(mTokens.at(11).lexeme, ")");
}

TEST_F(SingleTokensInLongSource, shouldScanEndOfFile) {
    EXPECT_EQ(mTokens.at(12).type, TokenType::EndOfFile);
}
