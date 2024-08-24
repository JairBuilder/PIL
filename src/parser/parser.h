#pragma once
#include "../lexer/lexer.h"
#include "../ast/ast.h"
#include "src/ast/expression_statement.h"
#include "src/ast/node.h"
#include "src/ast/program.h"
#include <list>
#include <memory>
using namespace pi::lexer;
using namespace pi::ast;

namespace pi {
    namespace parser {
        class Parser {
        public:
            enum Precedence {
                LOWEST = 0,
                SUM,        //+, -
                PRODUCT,    //*, /
            };
            Parser();
            Parser(const std::shared_ptr<Lexer>& lexer);
            ~Parser();

            using prefix_parse_fn = std::shared_ptr<Expression> (Parser::*)();
            using infix_parse_fn = std::shared_ptr<Expression> (Parser::*)(const std::shared_ptr<Expression>&);
            
            void next_token();
            bool curr_token_is(Token::Type type);
            bool peek_token_is(Token::Type type);
            bool expect_peek(Token::Type type);
            bool peek_error(Token::Type type);

            int curr_token_precedence();
            int peek_token_precedence();

            std::shared_ptr<Expression> parse_integer();
            std::shared_ptr<Expression> parse_group();

            std::shared_ptr<Program> parse_program();
            std::shared_ptr<Statement> parse_statement();
            std::shared_ptr<ExpressionStatement> parse_expression_statement();

            std::shared_ptr<Expression> parse_infix(const std::shared_ptr<Expression>& left);
            
            std::shared_ptr<Expression> parse_expression(int precedence);

            void no_prefix_parse_fn_error(Token::Type type);
            std::list<std::string> &errors();
        private:
            std::shared_ptr<Lexer> m_lexer;
            Token m_curr;   // current token
            Token m_peek;   // next token
            std::list<std::string> m_errors;
            static std::map<Token::Type, int> m_precedences;
            static std::map<Token::Type, prefix_parse_fn> m_prefix_parse_fns;
            static std::map<Token::Type, infix_parse_fn> m_infix_parse_fns;
        };
    }
}