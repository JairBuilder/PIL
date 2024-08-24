#include "parser.h"
using namespace pi::parser;

std::shared_ptr<Statement> Parser::parse_statement() {
    return parse_expression_statement();
}

std::shared_ptr<ExpressionStatement> Parser::parse_expression_statement() {
    std::shared_ptr<ExpressionStatement> s(new ExpressionStatement());
    s->m_expression = parse_expression(LOWEST);
    s->m_token = m_curr;
    while (peek_token_is(Token::TOKEN_SEMICOLON)) {
        next_token();
    }
    return s;
}