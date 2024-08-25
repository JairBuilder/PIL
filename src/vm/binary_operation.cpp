#include "src/object/integer.h"
#include "src/object/object.h"
#include "vm.h"
#include <memory>
using namespace pi::vm;

void VM::run_binary_operation(Code::Opcode op) {
    auto right=pop();
    auto left=pop();
    switch (left->type()) {
        case Object::OBJECT_INTEGER: {
            if (right->type()==Object::OBJECT_INTEGER) {
                run_binary_integer_operation(op, left, right);
            }
            break;
        }
        default: {
            break;
        }
    }
}

void VM::run_binary_integer_operation(Code::Opcode op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) {
    auto l=std::dynamic_pointer_cast<object::Integer>(left);
    auto r=std::dynamic_pointer_cast<object::Integer>(right);
    switch (op) {
        case Code::OP_ADD: {
            std::shared_ptr<object::Integer> obj(new object::Integer(l->m_value+r->m_value));
            push(obj);
            break;
        }
        case Code::OP_SUB: {
            std::shared_ptr<object::Integer> obj(new object::Integer(l->m_value-r->m_value));
            push(obj);
            break;
        }
        case Code::OP_MUL: {
            std::shared_ptr<object::Integer> obj(new object::Integer(l->m_value*r->m_value));
            push(obj);
            break;
        }
        case Code::OP_DIV: {
            std::shared_ptr<object::Integer> obj(new object::Integer(l->m_value/r->m_value));
            push(obj);
            break;
        }
        default: {
            break;
        }
    }
}
