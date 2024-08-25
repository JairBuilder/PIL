#include "compiler.h"
using namespace pi::compiler;

void Compiler::compile_infix(const std::shared_ptr<ast::Node> &node) {
    auto e = std::dynamic_pointer_cast<ast::Infix>(node);
    compile(e->m_left);
    compile(e->m_right);
    std::string op = e->m_operator;
    if (op == "+") {
        emit(Code::OP_ADD);
    } 
    else if (op == "-") {
        emit(Code::OP_SUB);
    } 
    else if (op == "*") {
        emit(Code::OP_MUL);
    } 
    else if (op == "/") {
        emit(Code::OP_DIV);
    }
}