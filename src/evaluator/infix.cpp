#include "evaluator.h"
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_infix(const std::string & op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right) {
    switch (left->type()) {
        case Object::OBJECT_INTEGER: {
            if (right->type()==Object::OBJECT_INTEGER) {
                return eval_integer_infix_expression(op, left, right);
            }
            break;
        }
        default: {
        }
    }
    return new_error("unknown operator: %s %s %s", left->name().c_str(), op.c_str(), right->name().c_str());
}

std::shared_ptr<Object> Evaluator::eval_integer_infix_expression(const std::string & op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right) {
    auto l = std::dynamic_pointer_cast<object::Integer>(left);
    auto r = std::dynamic_pointer_cast<object::Integer>(right);
    int64_t left_value = l->value();
    int64_t right_value = r->value();
    if (op == "+") {
        return new_integer(left_value + right_value);
    }
    if (op == "-") {
        return new_integer(left_value - right_value);
    }
    if (op == "*") {
        return new_integer(left_value * right_value);
    }   
    if (op == "/") {
        return new_integer(left_value / right_value);
    }
    return new_error("unknown operator: %s %s %s", left->name().c_str(), op.c_str(), right->name().c_str());
}



