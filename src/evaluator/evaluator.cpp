#include "evaluator.h"
#include "src/ast/integer.h"
#include "src/ast/program.h"
#include "src/object/object.h"
#include <memory>
using namespace pi::evaluator;

bool Evaluator::is_error(const std::shared_ptr<Object> &obj) {
    return obj->type() == Object::OBJECT_ERROR;
}
std::shared_ptr<Object> Evaluator::new_error(const char * format, ...) {
    char buf[1024] = "";
    va_list arg_ptr;
    va_start(arg_ptr, format);
    vsnprintf(buf, sizeof(buf), format, arg_ptr);
    va_end(arg_ptr);

    return std::shared_ptr<Error> (new object::Error(buf));
}
std::shared_ptr<Object> Evaluator::new_integer(int64_t value) {
    return Object::new_integer(value);
}
std::shared_ptr<Object> Evaluator::eval(const std::shared_ptr<Node>& node) {
    switch (node->type()) {
        case Node::NODE_PROGRAM : {
            auto s = std::dynamic_pointer_cast<ast::Program>(node);
            return eval_program(s->m_statements);
        }
        case Node::NODE_EXPRESSION_STATEMENT: {
            auto s = std::dynamic_pointer_cast<ExpressionStatement>(node);
            return eval(s->m_expression);
        }
        case Node::NODE_INTEGER: {
            auto e = std::dynamic_pointer_cast<ast::Integer>(node);
            return eval_integer(e);
        }
        case Node::NODE_INFIX:{
            auto e = std::dynamic_pointer_cast<ast::Infix>(node);
            auto left = eval(e->m_left);
            if (is_error(left)) {
                return left;
            }
            auto right = eval(e->m_right);
            if (is_error(right)) {
                return right;
            }
            return eval_infix(e->m_operator, left, right);   
        }
        default: {
            return new_error("node type error");
        }
    }
}