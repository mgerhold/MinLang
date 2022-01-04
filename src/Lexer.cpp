//
// Created by coder2k on 04.01.2022.
//

#include "Lexer.hpp"

using namespace std::string_view_literals;

std::vector<std::unique_ptr<Token>> Lexer::getTokens() {
    while (not isAtEnd()) {
        switch (peek()) {
            case '=':
                consume();
                addToken<Equals>("="sv);
                break;
            case ';':
                consume();
                addToken<Semicolon>(";"sv);
                break;
            case '+':
                consume();
                addToken<Plus>("+"sv);
                break;
            case '@':
                consume();
                addToken<At>("@"sv);
                break;
            case '"':
                stringLiteral();
                break;
            default:
                if (std::isspace(peek())) {
                    consume();
                    continue;
                }
                if (std::isdigit(peek())) {
                    numberLiteral();
                    break;
                }
                keywordOrIdentifier();
                break;
        }
    }
    addToken<EndOfFile>(""sv);
    return std::move(mTokens);
}

void Lexer::stringLiteral() {
    const auto startPosition = mCurrent;
    consume('"', "Expected '\"' at the start of a string literal.");
    while (not isAtEnd() and peek() != '"') {
        consume();
    }
    if (isAtEnd()) {
        throw error("Expected string termination, got end of file.");
    }
    consume('"', "Expected '\"' at the end of a string literal.");
    addToken<StringLiteral>(mSource.substr(startPosition, mCurrent - startPosition));
}

void Lexer::numberLiteral() {
    const auto startPosition = mCurrent;
    consume();
    while (not isAtEnd() and std::isdigit(peek())) {
        consume();
    }
    if (isAtEnd()) {
        throw error("Expected literal specifier at the end of a number literal, got end of file.");
    }
    consume('u', "Expected number literal specifier.");
    addToken<U64Literal>(mSource.substr(startPosition, mCurrent - startPosition + 1));
}

void Lexer::keywordOrIdentifier() {
    if (not std::isalpha(peek())) {
        throw error("Identifiers must start with a letter.");
    }
    const auto startPosition = mCurrent;
    while (not isAtEnd() and std::isalnum(peek())) {
        consume();
    }
    const auto lexeme = mSource.substr(startPosition, mCurrent - startPosition);
    if (lexeme == "const"sv) {
        addToken<Const>(lexeme);
    } else if (lexeme == "mutable"sv) {
        addToken<Mutable>(lexeme);
    } else if (lexeme == "print"sv) {
        addToken<Print>(lexeme);
    } else {
        addToken<Identifier>(lexeme);
    }
}

constexpr bool Lexer::isAtEnd() const {
    return (mCurrent >= mSource.length());
}

constexpr char Lexer::peek() const {
    return mSource.at(mCurrent);
}

constexpr bool Lexer::check(char toCheck) const {
    return peek() == toCheck;
}

constexpr void Lexer::consume() {
    if (peek() == '\n') {
        ++mLine;
        mColumn = 0;
    } else {
        ++mColumn;
    }
    ++mCurrent;
}

constexpr void Lexer::consume(char toConsume, const std::string& errorMessage) {
    if (!check(toConsume)) {
        throw LexerError(mLine, mColumn, errorMessage);
    }
    consume();
}

constexpr bool Lexer::match(char toMatch) {
    if (!check(toMatch)) {
        return false;
    }
    consume();
    return true;
}
LexerError Lexer::error(const std::string& message) const {
    return LexerError{ mLine, mColumn, message };
}
