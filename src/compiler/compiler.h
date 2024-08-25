#pragma once
#include "src/ast/ast.h"
#include "src/ast/program.h"
#include <memory>
using namespace pi::ast;
#include "src/object/object.h"
using namespace pi::object;
#include "src/code/instruction.h"
using namespace pi::code;

namespace pi {
    namespace compiler {
        class Compiler {
            public:
                Compiler()=default;
                ~Compiler()=default;
                void compile(const std::shared_ptr<ast::Node> &node);

                void show();
            public:
                std::vector<std::shared_ptr<Object>> m_constants;
                std::vector<std::shared_ptr<Instruction>> m_instructions;
                std::vector<std::shared_ptr<Object>> m_symbols;
            private:
                void compile_program(const std::shared_ptr<ast::Node> &node);
                void compile_expression_statement(const std::shared_ptr<ast::Node> &node);
                void compile_infix(const std::shared_ptr<ast::Node> &node);
                void compile_integer(const std::shared_ptr<ast::Node> &node);

                int emit(Code::Opcode op, const std::vector<int> & operands={});
                int add_constant(const std::shared_ptr<Object> &obj);
        };
    }
}