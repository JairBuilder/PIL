#include "src/object/integer.h"
#include "compiler.h"
#include <memory>
using namespace pi::compiler;

void Compiler::compile_integer(const std::shared_ptr<ast::Node> &node) {
    auto e = std::dynamic_pointer_cast<ast::Integer>(node);
    std::shared_ptr<object::Integer> obj(new object::Integer(e->m_value));
    int idx = add_constant(obj);
    emit(Code::OP_LOAD, {idx});
}
