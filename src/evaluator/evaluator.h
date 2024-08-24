#pragma once
#include <memory>
#include <string>

#include "src/ast/ast.h"
using namespace pi::ast;
#include "src/object/header.h"
#include <stdarg.h>
using namespace pi::object;
namespace pi {
    namespace evaluator {
        class Evaluator {
        public:
            Evaluator()=default;
            ~Evaluator()=default;

            bool is_error(const std::shared_ptr<Object> &obj);
            std::shared_ptr<Object> new_error(const char * format, ...);
            std::shared_ptr<Object> new_integer(int64_t value);
            std::shared_ptr<Object> eval(const std::shared_ptr<Node>& node);
            std::shared_ptr<Object> eval_program(const std::list<std::shared_ptr<ast::Statement>>& stmts);
            std::shared_ptr<Object> eval_integer(const std::shared_ptr<ast::Integer>& node);

            std::shared_ptr<Object> eval_infix(const std::string & op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right);
            std::shared_ptr<Object> eval_integer_infix_expression(const std::string & op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right);
        };
    }
}