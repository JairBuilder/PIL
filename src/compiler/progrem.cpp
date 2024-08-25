#include "compiler.h"
#include "src/ast/program.h"
#include <memory>
using namespace pi::compiler;

void Compiler::compile_program(const std::shared_ptr<ast::Node> &node) {
    auto e = std::dynamic_pointer_cast<ast::Program>(node);
    for (auto &stmt : e->m_statements) {
        compile(stmt);
    }
}