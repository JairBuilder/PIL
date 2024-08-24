#include "token.h"

using namespace pi::token;

std::map<Token::Type, std::string> Token::m_names = {
    {TOKEN_ILLEGAL,    "illegal"   },
    {TOKEN_EOF,        "eof"       },
    {TOKEN_INTEGER,    "integer"   },
    {TOKEN_PLUS,       "+"         },
    {TOKEN_MINUS,      "-"         },
    {TOKEN_ASTERISK,   "*"         },
    {TOKEN_SLASH,     "/"         },
    {TOKEN_LPAREN,     "("         },
    {TOKEN_RPAREN,     ")"         },
    {TOKEN_SEMICOLON,  ";"         }
};

Token::Token() : m_type(TOKEN_ILLEGAL) {}

Token::Token(Type type, const std::string& literal) : m_type(type), m_literal(literal) {}

std::string Token::name() const {
    auto it = m_names.find(m_type);
    if (it != m_names.end()) {
        return it->second;
    }
    return "";
}

Token::Type Token::type() {
    return m_type;
}

std::string Token::literal() {
    return m_literal;
}

Token& Token::operator=(const Token& other) {
    if (this == &other) {
        return *this;
    }
    m_type = other.m_type;
    m_literal = other.m_literal;
    return *this;
}

void Token::show() const {
    printf("tname: %s,\tliteral: %s\n", name().c_str(), m_literal.c_str());
}

