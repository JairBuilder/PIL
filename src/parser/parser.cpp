#include "parser.h"
#include <map>
#include <sstream>
using namespace pi::parser;

std::map<Token::Type, int> Parser::m_precedences = {
    {Token::TOKEN_PLUS,     SUM},
    {Token::TOKEN_MINUS,    SUM},
    {Token::TOKEN_SLASH,    PRODUCT},
    {Token::TOKEN_ASTERISK, PRODUCT}
};

std::map<Token::Type, Parser::prefix_parse_fn> Parser::m_prefix_parse_fns = {
    {Token::TOKEN_INTEGER,      &Parser::parse_integer},
    {Token::TOKEN_LPAREN,      &Parser::parse_group},
};

std::map<Token::Type, Parser::infix_parse_fn> Parser::m_infix_parse_fns = {
    {Token::TOKEN_PLUS,     &Parser::parse_infix},
    {Token::TOKEN_MINUS,    &Parser::parse_infix},
    {Token::TOKEN_SLASH,    &Parser::parse_infix},
    {Token::TOKEN_ASTERISK, &Parser::parse_infix},
};

Parser::Parser()
{

}

Parser::Parser(const std::shared_ptr<Lexer>& lexer)
{
    m_lexer = lexer;
    next_token(); // get the first token
    next_token(); // get the second token
}

Parser::~Parser()
{
}

void Parser::next_token()
{
    m_curr = m_peek;
    m_peek = m_lexer->next_token();
}

bool Parser::curr_token_is(Token::Type type)
{
    return m_curr.type() == type;
}

bool Parser::peek_token_is(Token::Type type)
{
    return m_peek.type() == type;
}

// 检查下一个标记是否与给定类型匹配，如果匹配则返回true，否则返回false
bool Parser::expect_peek(Token::Type type)
{
    if (peek_token_is(type))
    {
        next_token();
        return true;
    }
    else {
        peek_error(type);
        return false;
    }
}

bool Parser::peek_error(Token::Type type)
{
    std::ostringstream oss;
    oss << "expected next token to be " << type << ", got " << m_peek.type() << "instead";
    m_errors.push_back(oss.str());
    return false;
}

int Parser::curr_token_precedence() {
    auto it = m_precedences.find(m_curr.type());
    if (it == m_precedences.end())
        return LOWEST;
    return it->second;
}

int Parser::peek_token_precedence() {
    auto it = m_precedences.find(m_peek.type());
    if (it == m_precedences.end())
        return LOWEST;
    return it->second;
}

void Parser::no_prefix_parse_fn_error(Token::Type type)
{
    std::ostringstream oss;
    oss << "no prefix parse function for " << type << " found";
    m_errors.push_back(oss.str());
}

std::list<std::string>& Parser::errors() {
    return m_errors;
}