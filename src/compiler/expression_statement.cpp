#include "compiler.h"
using namespace pi::compiler;

void Compiler::compile_expression_statement(const std::shared_ptr<ast::Node> &node) {
    auto e = std::dynamic_pointer_cast<ast::ExpressionStatement>(node);
    compile(e->m_expression);
    emit(Code::OP_POP);
}