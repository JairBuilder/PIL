#include "src/ast/program.h"
#include "parser.h"
#include <memory>
using namespace pi::parser;

std::shared_ptr<Program> Parser::parse_program() {
    std::shared_ptr<Program> s(new Program());
    while (m_curr.type() != Token::Type::TOKEN_EOF) {
        auto stmt = parse_statement();
        if (stmt != nullptr) {
            s->m_statements.push_back(stmt);
        }
        next_token();
    }
    return s;
}