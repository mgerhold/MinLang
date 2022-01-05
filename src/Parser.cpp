//
// Created by coder2k on 05.01.2022.
//

#include "Parser.hpp"
#include "ParserError.hpp"
#include <iostream>

using enum TokenType;
using namespace std::string_view_literals;

Parser::Parser(const std::vector<Token>& tokens) : mTokens{ tokens } {
    assert(!tokens.empty());
    assert(tokens.back().type == TokenType::EndOfFile);
}

ASTNode Parser::parse() {
    try {
        return expression();
    } catch (const ParserError& error) {
        std::cerr << "Parser error: " << error.what() << "\n";
    }
    return {};
}

ASTNode Parser::expression() {
    return primary();
}

ASTNode Parser::primary() {
    if (match(LeftParenthesis)) {
        return grouping();
    }
    if (peek().type == StringLiteral) {
        return std::make_unique<StringLiteralExpr>(consume());
    }
    if (peek().type == U64Literal) {
        return std::make_unique<U64LiteralExpr>(consume());
    }
    throw ParserError{ peek(), "Expected primary expression."sv };
}

ASTNode Parser::grouping() {
    auto subExpression = expression();
    consume(RightParenthesis, "Expecting ')' at the end of grouping expression."sv);
    return subExpression;
}

const Token& Parser::peek() const {
    return mTokens.at(mCurrent);
}

bool Parser::isAtEnd() const {
    return peek().type == EndOfFile;
}

Token Parser::consume() {
    if (not isAtEnd()) {
        return mTokens.at(mCurrent++);
    }
    return peek();
}

Token Parser::consume(TokenType expect, std::string_view errorMessage) {
    if (not check(expect)) {
        throw ParserError{ peek(), errorMessage };
    }
    return consume();
}

bool Parser::match(TokenType type) {
    if (peek().type != type) {
        return false;
    }
    consume();
    return true;
}

bool Parser::check(TokenType type) const {
    return peek().type == type;
}
