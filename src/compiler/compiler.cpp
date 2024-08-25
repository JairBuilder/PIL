#include "compiler.h"
#include "src/code/instruction.h"
#include <memory>
using namespace pi::compiler;

void Compiler::compile(const std::shared_ptr<ast::Node> &node) {
    switch (node->type()) {
        case Node::NODE_PROGRAM : {
            compile_program(node);
            break;
        }
        case Node::NODE_EXPRESSION_STATEMENT : {
            compile_expression_statement(node);
            break;
        }
        case Node::NODE_INFIX : {
            compile_infix(node);
            break;
        }
        case Node::NODE_INTEGER : {
            compile_integer(node);
            break;
        }
        default:{
            break;
        }
    }
}

int Compiler::emit(Code::Opcode op, const std::vector<int> & operands) {
    std::shared_ptr<Instruction> ins(new Instruction());
    ins->make(op, operands);
    m_instructions.push_back(ins);
    return m_instructions.size() - 1;
}

int Compiler::add_constant(const std::shared_ptr<Object> &obj) {
    m_constants.push_back(obj);
    return m_constants.size() - 1;
}   

void Compiler::show() {
    std::cout<<"constants:"<<std::endl;
    for (int i = 0; i < m_constants.size(); i++) {
        auto obj = m_constants[i];
        std::cout<<"\tconstants["<<i<<"] = "<<obj->str()<<std::endl;
    }

    std::cout<<"instructions:"<<std::endl;
    for (int i = 0; i < m_instructions.size(); i++) {
        auto ins = m_instructions[i];
        printf("\t%04d %s\n",i,m_instructions[i]->str().c_str());
    }
}

