#pragma once
#include "src/token/token.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace pi::token;
namespace pi {
    namespace lexer {
        class Lexer {
        public:
            Lexer(const std::string& inputFile);
            Lexer();
            ~Lexer() = default;
            Token next_token();

        private:    
            char m_ch;
            std::string m_input;
            int m_pos;
            int m_next_pos;

        private:
            void skip_white_space();
            void read_char();
            void unread_char();
            bool is_digit(char ch);
            std::string read_number();
            Token new_token(Token::Type type, const std::string& literal);
        };
    }
}