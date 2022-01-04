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
    ASSERT_TRUE(dynamic_cast<Const*>(tokens.front().get()));
    ASSERT_TRUE(dynamic_cast<EndOfFile*>(tokens.back().get()));
}

class SingleTokensInLongSource : public ::testing::Test {
public:
    void SetUp() override {
        const auto source = R"(const thisIsAnIdentifier054Test="string literal";mutable 4297243u+print@)"sv;
        auto lexer = Lexer{ source };
        mTokens = lexer.getTokens();
        ASSERT_EQ(mTokens.size(), 11);
    }

protected:
    std::vector<std::unique_ptr<Token>> mTokens;
};

TEST_F(SingleTokensInLongSource, shouldScanConst) {
    ASSERT_TRUE(dynamic_cast<Const*>(mTokens.at(0).get()));
    EXPECT_EQ(dynamic_cast<Const*>(mTokens.at(0).get())->lexeme, "const");
}

TEST_F(SingleTokensInLongSource, shouldScanIdentifier) {
    ASSERT_TRUE(dynamic_cast<Identifier*>(mTokens.at(1).get()));
    EXPECT_EQ(dynamic_cast<Identifier*>(mTokens.at(1).get())->lexeme, "thisIsAnIdentifier054Test");
}

TEST_F(SingleTokensInLongSource, shouldScanEquals) {
    ASSERT_TRUE(dynamic_cast<Equals*>(mTokens.at(2).get()));
    EXPECT_EQ(dynamic_cast<Equals*>(mTokens.at(2).get())->lexeme, "=");
}

TEST_F(SingleTokensInLongSource, shouldScanStringLiteral) {
    ASSERT_TRUE(dynamic_cast<StringLiteral*>(mTokens.at(3).get()));
    EXPECT_EQ(dynamic_cast<StringLiteral*>(mTokens.at(3).get())->lexeme, R"("string literal")");
    EXPECT_EQ(dynamic_cast<StringLiteral*>(mTokens.at(3).get())->value(), "string literal");
}

TEST_F(SingleTokensInLongSource, shouldScanSemicolon) {
    ASSERT_TRUE(dynamic_cast<Semicolon*>(mTokens.at(4).get()));
}

TEST_F(SingleTokensInLongSource, shouldScanMutable) {
    ASSERT_TRUE(dynamic_cast<Mutable*>(mTokens.at(5).get()));
}

TEST_F(SingleTokensInLongSource, shouldScanU64Literal) {
    ASSERT_TRUE(dynamic_cast<U64Literal*>(mTokens.at(6).get()));
    EXPECT_EQ(dynamic_cast<U64Literal*>(mTokens.at(6).get())->value(), 4297243);
}

TEST_F(SingleTokensInLongSource, shouldScanPlus) {
    ASSERT_TRUE(dynamic_cast<Plus*>(mTokens.at(7).get()));
}

TEST_F(SingleTokensInLongSource, shouldScanPrint) {
    ASSERT_TRUE(dynamic_cast<Print*>(mTokens.at(8).get()));
}

TEST_F(SingleTokensInLongSource, shouldScanAt) {
    ASSERT_TRUE(dynamic_cast<At*>(mTokens.at(9).get()));
}

TEST_F(SingleTokensInLongSource, shouldScanEndOfFile) {
    ASSERT_TRUE(dynamic_cast<EndOfFile*>(mTokens.at(10).get()));
}
