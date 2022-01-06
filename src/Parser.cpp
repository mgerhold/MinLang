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

StatementList Parser::parse() {
    StatementList statements;
    try {
        while (not isAtEnd()) {
            statements.push_back(statement());
        }
    } catch (const ParserError& error) {
        std::cerr << "Parser error: " << error.what() << "\n";
        hadError = true;
    }
    return statements;
}

StmtNode Parser::statement() {
    if (match(Print)) {
        return printStatement();
    }
    return exprStatement();
}

StmtNode Parser::exprStatement() {
    auto expr = expression();
    consume(Semicolon, "Expected ';' at the end of expression statement."sv);
    return std::make_unique<ExpressionStatement>(previous(), std::move(expr));
}

StmtNode Parser::printStatement() {
    auto toPrint = expression();
    auto statement = std::make_unique<PrintStatement>(previous(), std::move(toPrint));
    consume(Semicolon, "Expected ';' after the expression that should be printed."sv);
    return statement;
}

ExprNode Parser::expression() {
    return primary();
}

ExprNode Parser::primary() {
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

ExprNode Parser::grouping() {
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

Token Parser::previous() const {
    return mTokens.at(mCurrent - 1);
}
