#include "parser.h"
using namespace pi::parser;

std::shared_ptr<Expression> Parser::parse_group()
{
    next_token();// 跳过左括号
    auto e = parse_expression(LOWEST);// 解析表达式
    if (!expect_peek(Token::TOKEN_RPAREN)) {// 检查右括号
        return nullptr;
    }
    return e;
}