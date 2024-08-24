#include "lexer.h"
#include <sstream>
using namespace pi::lexer;

Lexer::Lexer(const std::string& inputFile)
    : m_input(inputFile)
    , m_pos(0)
    , m_next_pos(0)
    , m_ch(0)
{
    std::ifstream ifs(inputFile);
    if (!ifs.good()) {
        std::cerr << "File not found: " << inputFile << std::endl;
        return;
    }
    std::ostringstream oss;
    oss << ifs.rdbuf();
    m_input = oss.str();
}

Lexer::Lexer() : m_pos(0), m_next_pos(0), m_ch(0) {}

void Lexer::skip_white_space()
{
    while (m_ch == ' ' || m_ch == '\t' || m_ch == '\n' || m_ch == '\r') {
        read_char();
    }
}

void Lexer::read_char()
{
    if (m_next_pos >= m_input.length()) {
        m_ch = 0;
    } else {
        m_ch = m_input[m_next_pos];
    }
    m_pos = m_next_pos;
    m_next_pos += 1;
}

void Lexer::unread_char()
{
    m_next_pos = m_pos;
    m_pos--;
}

bool Lexer::is_digit(char ch)
{
    return '0' <= ch && ch <= '9';
}

std::string Lexer::read_number()
{
    int pos = m_pos;
    while (is_digit(m_ch)) {
        read_char();
    }
    return m_input.substr(pos, m_pos - pos);
}

Token Lexer::new_token(Token::Type type, const std::string& literal)
{
    return Token(type, literal);
}

Token Lexer::next_token()
{
    read_char();
    skip_white_space();
    switch (m_ch) {
    case ';': {
        std::string literal;
        literal+=m_ch;
        return new_token(Token::Type::TOKEN_SEMICOLON, literal);
    }
    case '(': {
        std::string literal;
        literal+=m_ch;
        return new_token(Token::Type::TOKEN_LPAREN, literal);
    }
    case ')': {
        std::string literal;
        literal+=m_ch;
        return new_token(Token::Type::TOKEN_RPAREN, literal);
    }
    case '+': {
        std::string literal;
        literal+=m_ch;
        return new_token(Token::Type::TOKEN_PLUS, literal);
    }
    case '-': {
        std::string literal;
        literal+=m_ch;
        return new_token(Token::Type::TOKEN_MINUS, literal);
    }
    case '*': {
        std::string literal;
        literal+=m_ch;
        return new_token(Token::Type::TOKEN_ASTERISK, literal);
    }
    case '/': {
        std::string literal;
        literal+=m_ch;
        return new_token(Token::Type::TOKEN_SLASH, literal);
    }
    case 0: {
        return new_token(Token::Type::TOKEN_EOF, "");
    }
    default:
        if (is_digit(m_ch)) {
            std::string literal = read_number();
            unread_char();
            return new_token(Token::Type::TOKEN_INTEGER, literal);
        } else {
            std::string literal;
            literal+=m_ch;
            return new_token(Token::Type::TOKEN_ILLEGAL, literal);
        }
    }
}
