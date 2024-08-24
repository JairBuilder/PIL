#pragma once
#include <iostream>
#include <string>
#include <map>

namespace pi {
    namespace token {
        class Token {
        public:
            enum Type {
                TOKEN_ILLEGAL,
                TOKEN_EOF,
                TOKEN_INTEGER,
                TOKEN_PLUS,
                TOKEN_MINUS,
                TOKEN_ASTERISK,
                TOKEN_SLASH,
                TOKEN_LPAREN,
                TOKEN_RPAREN,
                TOKEN_SEMICOLON
            };

            Token(Type type, const std::string& literal);
            Token();
            ~Token() {}

            std::string name() const;
            Type type();
            std::string literal();
            Token& operator=(const Token& other);
            void show() const;
        private:
            Type m_type;
            std::string m_literal;
            static std::map<Type, std::string> m_names;
        };
    }
}